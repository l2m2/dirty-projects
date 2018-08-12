from django.shortcuts import render
from django.views import View

class PersonalCenterView(View):
    def get(self, request):
        print("FUCK")