#!/usr/bin/env python3
import serial
import time
import json
from pycoingecko import CoinGeckoAPI

def makeApiCall():
  cg = CoinGeckoAPI()
  coingeckoresponse = cg.get_price(ids='bitcoin,litecoin,ethereum,ripple,cardano,solana', vs_currencies='chf')
  responseToWire = json.dumps(coingeckoresponse)
  print(responseToWire)
  return responseToWire

if __name__ == '__main__':
    #Serial communication
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    

    while True:
        res = makeApiCall()
        ser.write((res + '\n').encode())
        time.sleep(30)
