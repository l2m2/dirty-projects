from django.urls import include, path
from Page import views

urlpatterns = [
    path('', views.PageView.as_view()),
]