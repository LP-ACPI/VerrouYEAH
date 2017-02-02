/* -*- Mode: C; indent-tabs-mode:t ; c-basic-offset:8 -*- */
/*
 * 
 * Copyright © 2012-2013 Nathan Hjelm <hjelmn@mac.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * http://libusb.info/
 * 
 * https://github.com/libusb/libusb
 *
 * 
 *
 * exemple d'utilisation de libusb pour lister puis détecter "hotplug API" sur USB
 *
 * librairie jointe relativement mais peut être installée comme paquet:
 *  sudo apt-get install libusb-1.0-0-dev
 *
 * mais changer ensuite "libusb.h" en  <libusb-1.0/libusb.h> (ou modifier ses chemins include)
 *
 * à compiler avec linker -lusb-10:
 *
 * g++ main.cpp -o test -lusb-1.0
 * 
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libusb.h"
// #include "stdint.h"

/**
 * [imprimer les infos d'un seul périph' USB]
 * @param dev [description]
 */
static void print_one_dev(libusb_device *dev){
    struct libusb_device_descriptor desc;
    int j = 0;
    uint8_t path[8]; 
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
      fprintf(stderr, "failed to get device descriptor");
      return;
    }

    printf("pid:%04x|vid:%04x (bus %d, device %d)",desc.idVendor, desc.idProduct,libusb_get_bus_number(dev), libusb_get_device_address(dev));

    r = libusb_get_port_numbers(dev, path, sizeof(path));
    if (r > 0) {
      printf(" path: %d", path[0]);
      for (j = 1; j < r; j++)
        printf(".%d", path[j]);
    }
    printf("\n");
}
/**
 * [imprimmer la liste de périphs' USB détectés]
 * @param devs [pointeur sur structure libusb_device - gestion périphériques usb]
 */
static void print_devs(libusb_device **devs)
{
  int i = 0;
  libusb_device *dev;
  while ((dev = devs[i++]) != NULL) {
    print_one_dev(dev);
  }
}

libusb_device_handle *handle = NULL;
/**
 * [fonction appelée sur insertion du périphérique]
 * @param  ctx       [contexte]
 * @param  dev       [structure "périphérique"]
 * @param  event     [évennement enregistré]
 * @param  user_data [données]
 * @return           [ = 0]
 */
static int LIBUSB_CALL hotplug_callback(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data)
{

  printf ("add: \t");
  print_one_dev(dev);
  if (handle) {
    libusb_close (handle);
    handle = NULL;
  }
/* perso, j'ai toujours des erreurs quand il 
  rc = libusb_open (dev, &handle);
  if (LIBUSB_SUCCESS != rc) {
    fprintf (stderr, "Error opening device\n");
  }
*/
  return 0;
}
/**
 * [fonction appelée sur détection du détachement de périphérique]
 * @param  ctx       [description]
 * @param  dev       [description]
 * @param  event     [description]
 * @param  user_data [description]
 * @return           [description]
 */
static int LIBUSB_CALL hotplug_callback_detach(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data)
{
  
  printf ("removed: \t");
  print_one_dev(dev);

  if (handle) {
    libusb_close (handle);
    handle = NULL;
  }

  return 0;
}

int main(int argc, char *argv[])
{
   /*pour la liste*/
  libusb_device **devs;
  ssize_t cnt;

  /* pour la détection*/
  libusb_hotplug_callback_handle hp[2];
  int product_id, vendor_id, class_id;
  int rc;

/* si jamais on cherche un périphérique particulier à indiquer en params*/
  vendor_id  = (argc > 1) ? (int)strtol (argv[1], NULL, 0) : LIBUSB_HOTPLUG_MATCH_ANY;
  product_id = (argc > 2) ? (int)strtol (argv[2], NULL, 0) : LIBUSB_HOTPLUG_MATCH_ANY;
  class_id   = (argc > 3) ? (int)strtol (argv[3], NULL, 0) : LIBUSB_HOTPLUG_MATCH_ANY;

  rc = libusb_init (NULL);
  if (rc < 0)
  {
    printf("failed to initialise libusb: %s\n", libusb_error_name(rc));
    return EXIT_FAILURE;
  }

  /*compter le nombre de USBs détectés */
  cnt = libusb_get_device_list(NULL, &devs);
  if (cnt < 0)
    return (int) cnt;

/*les imprimer */
  print_devs(devs);
  libusb_free_device_list(devs, 1);

  if (!libusb_has_capability (LIBUSB_CAP_HAS_HOTPLUG)) {
    printf ("Hotplug capabilites are not supported on this platform\n");
    libusb_exit (NULL);
    return EXIT_FAILURE;
  }

  rc = libusb_hotplug_register_callback (NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED,(libusb_hotplug_flag) 0, vendor_id,
    product_id, class_id, hotplug_callback, NULL, &hp[0]);
  if (LIBUSB_SUCCESS != rc) {
    fprintf (stderr, "Error registering callback 0\n");
    libusb_exit (NULL);
    return EXIT_FAILURE;
  }

  rc = libusb_hotplug_register_callback (NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, (libusb_hotplug_flag) 0, vendor_id,
    product_id,class_id, hotplug_callback_detach, NULL, &hp[1]);
  if (LIBUSB_SUCCESS != rc) {
    fprintf (stderr, "Error registering callback 1\n");
    libusb_exit (NULL);
    return EXIT_FAILURE;
  }

  int t; // petit drapeau pour indiquer la fin de l'évennement (attache/détache)
  while (1) {/* boucle de détection d'évennement sur ports USBs */
    rc = libusb_handle_events_completed(NULL, &t);
    if (rc < 0)
      printf("libusb_handle_events_completed() failed: %s\n", libusb_error_name(rc));
  }

  if (handle) {
    libusb_close (handle);
  }

  libusb_exit (NULL);

  return EXIT_SUCCESS;
}