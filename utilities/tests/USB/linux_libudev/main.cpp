#include <libudev.h>
/* List and monitor USB devices using libudev.
 *
 * https://www.kernel.org/pub/linux/utils/kernel/hotplug/libudev/ch01.html
 *
 * app-get installl libudev-dev
 * 
 * à compiler avec linker -ludev
 *
 *  "g++ main.cpp -o test -ludev"
 * 
 */
#include <stdio.h>

//on observe les USB
#define SUBSYSTEM_USB "usb"

/**
 * [imprimer les informations contenues dans structure dev]
 * @param dev [pointeur udev_device: informations récupérées de /dev de unix]
 */
static void print_device(struct udev_device* dev)
{
    const char* action = udev_device_get_action(dev);
    if (! action)
        action = "exists";

    const char* vendor = udev_device_get_sysattr_value(dev, "idVendor");
    if (! vendor)
        vendor = "0000";

    const char* product = udev_device_get_sysattr_value(dev, "idProduct");
    if (! product)
        product = "0000";

    printf("%s %s %6s %s:%s %s\n",
           udev_device_get_subsystem(dev),
           udev_device_get_devtype(dev),
           action,
           vendor,
           product,
           udev_device_get_devnode(dev));
}

/**
 * [vérifications préalables avant l'impression des infos du périph' usb]
 * @param dev [structure udev_device (ptr vers)]
 */
static void process_device(struct udev_device* dev)
{
    if (dev) {
        if (udev_device_get_devnode(dev))
            print_device(dev);

        udev_device_unref(dev);
    }
}

/**
 * fonction imprimant la liste de périph' USB détectés sur la machine
 * @param udev [pointeur sur une structure udev - gestionnaire de périph' linux]
 */
static void enumerate_devices(struct udev* udev)
{
    struct udev_enumerate* enumerate = udev_enumerate_new(udev);

    udev_enumerate_add_match_subsystem(enumerate, SUBSYSTEM_USB);
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry* devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry* entry;

    udev_list_entry_foreach(entry, devices) {
        const char* path = udev_list_entry_get_name(entry);
        struct udev_device* dev = udev_device_new_from_syspath(udev, path);
        process_device(dev);
    }

    udev_enumerate_unref(enumerate);
}

/**
 * [boucle qui observe ce qui se passe sur les ports usb]
 * @param udev [pointeur vers structure udev  gestionnaire de périph' linux]
 */
static void monitor_devices(struct udev* udev)
{
    struct udev_monitor* mon = udev_monitor_new_from_netlink(udev, "udev");

    udev_monitor_filter_add_match_subsystem_devtype(mon, SUBSYSTEM_USB, NULL);
    udev_monitor_enable_receiving(mon);

    int fd = udev_monitor_get_fd(mon);

    while (1) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        int ret = select(fd+1, &fds, NULL, NULL, NULL);
        if (ret <= 0)
            break;

        if (FD_ISSET(fd, &fds)) {
            struct udev_device* dev = udev_monitor_receive_device(mon);
            process_device(dev);
        }
    }
}

int main(void)
{
    struct udev* udev = udev_new();
    if (!udev) {
        fprintf(stderr, "udev_new() failed\n");
        return 1;
    }

    enumerate_devices(udev);
    monitor_devices(udev);

    udev_unref(udev);
    return 0;
}