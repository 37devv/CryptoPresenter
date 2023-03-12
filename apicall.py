#!/usr/bin/env python3
import serial
import time
import json
from pycoingecko import CoinGeckoAPI

if __name__ == '__main__':
    #Serial communication
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    
    #API loop
    print("before while true loop")
    cg = CoinGeckoAPI()
    coingeckoresponse = cg.get_price(ids='bitcoin,litecoin,ethereum,ripple,cardano,solana', vs_currencies='chf')
    responseToWire = json.dumps(coingeckoresponse)
    print(responseToWire)
    
    #true loop
    while True:
        ser.write(responseToWire.encode())
        print("writing")
        #line = ser.readline().decode('utf-8').rstrip()
        #print(line)
        time.sleep(1)