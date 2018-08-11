from django.conf.urls import url
from Page import views

urlpatterns = [
    url(r'^$', views.PageView.as_view()),
]