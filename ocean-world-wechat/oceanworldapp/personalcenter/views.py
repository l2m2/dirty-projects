from django.shortcuts import render, HttpResponseRedirect
from django.views import View

class PersonalCenterView(View):
    def get(self, request):
        print("FUCK")
        return HttpResponseRedirect("/person/oo9gT0uTXxr_jcmq9Sqg6tTbpvss")