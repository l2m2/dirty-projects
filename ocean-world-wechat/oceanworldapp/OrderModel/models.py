from django.db import models

# Create your models here.
class Order(models.Model):
  wechatno = models.CharField(max_length=255)
  orderno = models.CharField(max_length=255)
  content = models.TextField()
  status = models.CharField(max_length=20)
  createtime = models.DateTimeField()