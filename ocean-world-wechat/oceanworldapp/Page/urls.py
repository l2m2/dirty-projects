from django.conf.urls import url
from Page import views

urlpatterns = [
    url('', views.PageView.as_view()),
]