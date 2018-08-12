"""oceanworldapp URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import include, path, re_path
from django.conf.urls import url

from werobot.contrib.django import make_view
from robot.robot import robot

from personalcenter.views import PersonalCenterView

urlpatterns = [
    path('admin/', admin.site.urls),
    path('robot', make_view(robot)),
    path('api/', include('api.urls')),
    path('personalcenter', PersonalCenterView.as_view()),
    path('', include('Page.urls')),
    path('layout', include('Page.urls')),
    re_path(r'^person/.*', include('Page.urls')),
    re_path('service.asmx?op=GetProducts', 'http://otaapi.galasystec.net.cn/service.asmx?op=GetProducts'),
]
