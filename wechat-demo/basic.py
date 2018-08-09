# -*- coding: utf-8 -*-
# filename: basic.py
import urllib2
import time
import json

class Basic:    
    def __init__(self):        
        self.__accessToken = ''        
        self.__leftTime = 0    
    def __real_get_access_token(self):
        appId = "wx0328a45eebc76a6d"        
        appSecret = "168b9d0da865f46619713dd13ed6ab28"        
        postUrl = ("https://api.weixin.qq.com/cgi-bin/token?grant_type=client_credential&appid=%s&secret=%s" % (appId, appSecret))        
        urlResp = urllib2.urlopen(postUrl)
        urlResp = json.loads(urlResp.read())                
        self.__accessToken = urlResp['access_token']        
        self.__leftTime = urlResp['expires_in']    
    def get_access_token(self):        
        if self.__leftTime < 10:            
            self.__real_get_access_token()        
        return self.__accessToken    
    def run(self):        
        while(True):            
            if self.__leftTime > 10:                
                time.sleep(2)                
                self.__leftTime -= 2            
            else:                
                self.__real_get_access_token()
