from django.shortcuts import render, HttpResponseRedirect
from django.views import View
from robot.robot import client

class PersonalCenterView(View):
    def get(self, request):
        print("FUCK")
        return HttpResponseRedirect("/person/14")