from django.db import models

# Create your models here.
class UserInfo(models.Model):
  wechatno = models.CharField(max_length=255, unique=True)
  fullname = models.CharField(max_length=255, blank=True)
  cellphone = models.CharField(max_length=40)
  sex = models.CharField(max_length=20, blank=True)
  email = models.CharField(max_length=40, blank=True)
  province = models.CharField(max_length=40, blank=True)
  address = models.CharField(max_length=1023, blank=True)
  id_card = models.CharField(max_length=20, blank=True)
