import ipaddress
import socket


class TcpScanner:
    def __init__(self, ip=input("Enter ip address: "), port=int(input("Enter port number: "))):
        self.ip = ip
        self.port = port

    def scan_port(self, port, timeout=0.01):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(timeout)
        try:
            s.connect((self.ip, port))
            print("Port %d: OPEN" % (port,))
            return True
        except ConnectionRefusedError:
            return False
        except OSError:
            return False
        finally:
            s.close()

    def port_lister(self):
        open_ports = {}
        for port in range(65535):
            portscan = self.scan_port(port)
            open_ports[port] = portscan
        return open_ports

    def scan_network(self, ip, timeout=0.01):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        socket.setdefaulttimeout(timeout)
        try:
            s.connect((ip, self.port))
            print("Port %d: OPEN at %s" % (self.port, ip))
            return True
        except ConnectionRefusedError as error:
            print(error)
            return False
        except OSError as error:
            print(error)
            return False
        finally:
            s.close()

    def port_at_ip(self):
        open_ip = {}
        ip = self.ip + '/8'
        for i in ipaddress.ip_network(ip, strict=False):
            portscan = self.scan_network(str(i))
            open_ip[i] = portscan
        return open_ip


if __name__ == "__main__":
    target = TcpScanner()
    print("-------- ex1 --------")
    res = target.port_lister()
    print("-------- ex2 --------")
    ret = target.port_at_ip()



