#include <stdlib.h>
#include <unistd.h>
int main()
{
    sleep(15);
    system("wpa_supplicant -D nl80211 -i wlan0 -c /etc/wpa_supplicant.conf -B");
    system("wpa_cli -i wlan0 scan");
    system("wpa_cli -i wlan0 add_network");
    system("wpa_cli -i wlan0 set_network 1 ssid '\"LAPTOP-FQASV313\"'");
    system("wpa_cli -i wlan0 set_network 1 psk '\"12345678\"'");
    system("wpa_cli -i wlan0 select_network 1");
    sleep(8);
    system("udhcpc -i wlan0");
    sleep(2);
    system("echo \"nameserver 114.114.114.114\" > /etc/resolv.conf");
    system("echo \"nameserver 8.8.8.8\" >> /etc/resolv.conf");
    return 0;
}