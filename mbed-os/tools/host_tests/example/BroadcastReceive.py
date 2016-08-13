"""
mbed SDK
Copyright (c) 2011-2013 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""
import socket
from time import sleep, time

BROADCAST_PORT = 58080

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('', BROADCAST_PORT))
while True:
    print s.recvfrom(256)
    data = 'Hello World: ' + repr(time()) + '\n'
    sent = s2.sendto(data, ('192.168.1.62', BROADCAST_PORT + 1))
    print "Sent Bytes:", sent
    sleep(10)
