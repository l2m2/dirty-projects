from django.shortcuts import render
from django.views import View
from werobot.client import Client
from robot.robot import cfg 

class PersonalCenterView(View):
    def get(self, request):
        ret = Client(config=cfg).grant_token()
        print(ret)