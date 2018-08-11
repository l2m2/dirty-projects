from django.shortcuts import render
from django.http import JsonResponse

def NoticeOrder(request):
  if request.method=="POST":
    data = {"ResultCode":"00","ResultMsg":"操作成功"}
    print(request.POST)
    return JsonResponse(data)