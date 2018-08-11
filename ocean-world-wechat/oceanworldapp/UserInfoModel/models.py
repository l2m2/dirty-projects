from django.db import models

# Create your models here.
class UserInfoModel(models.Model):
  fullname = models.CharField(max_length=255)
  cellphone = models.CharField(max_length=40)
  sex = models.CharField(max_length=20)
  email = models.CharField(max_length=40)
  province = models.CharField(max_length=40)
  address = models.CharField(max_length=1023)
  id_card = models.CharField(max_length=20)
