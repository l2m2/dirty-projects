# -*- coding: utf-8 -*-
# filename: menu.py
import urllib2
import sys
from basic import Basic

reload(sys)
sys.setdefaultencoding('utf8')

class Menu(object):
    def __init__(self):
        pass
    def create(self, postData, accessToken):
        postUrl = "https://api.weixin.qq.com/cgi-bin/menu/create?access_token=%s" % accessToken
        if isinstance(postData, unicode):
            postData = postData.encode('utf-8')
        urlResp = urllib2.urlopen(url=postUrl, data=postData)
        print urlResp.read()

    def query(self, accessToken):
        postUrl = "https://api.weixin.qq.com/cgi-bin/menu/get?access_token=%s" % accessToken
        urlResp = urllib2.urlopen(url=postUrl)
        print urlResp.read()

    def delete(self, accessToken):
        postUrl = "https://api.weixin.qq.com/cgi-bin/menu/delete?access_token=%s" % accessToken
        urlResp = urllib2.urlopen(url=postUrl)
        print urlResp.read()

    #获取自定义菜单配置接口
    def get_current_selfmenu_info(self, accessToken):
        postUrl = "https://api.weixin.qq.com/cgi-bin/get_current_selfmenu_info?access_token=%s" % accessToken
        urlResp = urllib2.urlopen(url=postUrl)
        print urlResp.read()

if __name__ == '__main__':
    myMenu = Menu()
    postJson = """
    {
        "button":
        [
            {
                "name": "入园必看",
                "sub_button":  
                [
                    {
                        "type": "view",
                        "name": "集团官网",
                        "url": "http://mp.weixin.qq.com/wiki?t=resource/res_main&id=mp1418702138&token=&lang=zh_CN"
                    },
                    {
                        "type": "view",
                        "name": "景区介绍",
                        "url": "http://mp.weixin.qq.com/wiki?t=resource/res_main&id=mp1418702138&token=&lang=zh_CN"
                    },
                    {
                        "type": "view",
                        "name": "动物科普",
                        "url": "http://mp.weixin.qq.com/wiki?t=resource/res_main&id=mp1418702138&token=&lang=zh_CN"
                    },
                    {
                        "type": "view",
                        "name": "表演时间",
                        "url": "http://mp.weixin.qq.com/wiki?t=resource/res_main&id=mp1418702138&token=&lang=zh_CN"
                    },
                    {
                        "type": "view",
                        "name": "游览攻略",
                        "url": "http://mp.weixin.qq.com/wiki?t=resource/res_main&id=mp1418702138&token=&lang=zh_CN"
                    }
                ]
                
            },
            {
                "name": "最新信息",
                "sub_button":
                [
                    {
                        "type": "view",
                        "name": "主题活动",
                        "url": "http://mp.weixin.qq.com/wiki?t=resource/res_main&id=mp1418702138&token=&lang=zh_CN"
                    },
                    {
                        "type": "view",
                        "name": "招聘信息",
                        "url": "http://mp.weixin.qq.com/wiki?t=resource/res_main&id=mp1418702138&token=&lang=zh_CN"
                    },
                    {
                        "type": "view",
                        "name": "有奖调研",
                        "url": "http://mp.weixin.qq.com/wiki?t=resource/res_main&id=mp1433747234&token=&lang=zh_CN"
                    }
                ]
            },
            {
                "name": "购票服务",
                "sub_button": 
                [
                    {
                        "type": "view",
                        "name": "个人中心",
                        "url": "http://mp.weixin.qq.com/wiki?t=resource/res_main&id=mp1418702138&token=&lang=zh_CN"
                    },
                    {
                        "type": "view",
                        "name": "一键购票",
                        "url": "https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx8c53a82f87f6fe0d&redirect_uri=http%3A%2F%2Fjkb66.com%2Fweixinwap.jhtml%3FredirectUrl%3Dhttp%253A%252F%252Fjkb66.com%252FjikebaoPage%252Fpage%252Fwxstore%252Findex.html%253FmemberId%253D17393%2526wid%253D2365%2526openid%253Doo9gT0uTXxr_jcmq9Sqg6tTbpvss%2526source%253Dstore&response_type=code&scope=snsapi_base&state=user-openid&component_appid=wxecc6883e97ebcf71&connect_redirect=1#wechat_redirect"
					}
                ]
            }
          ]
    }
    """
    accessToken = Basic().get_access_token()
    #myMenu.delete(accessToken)
    myMenu.create(postJson, accessToken)
