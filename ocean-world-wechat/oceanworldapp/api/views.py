from django.shortcuts import render
from django.http import JsonResponse
from django.core.cache import cache

def NoticeOrder(request):
  if request.method=="POST":
    data = {"ResultCode":"00","ResultMsg":"操作成功"}
    print(request.POST)
    return JsonResponse(data)

def GetUserInfo(request):
  if request.method == "GET":
    return JsonResponse({"code": 1, "message": "未传入用户ID."})
    # openid = request.GET.get('id', '')
    # if openid == '':
    #   return JsonResponse({"code": 1, "message": "未传入用户ID."})
    # else:
    #   userinfo = cache.get(openid)
    #   if userinfo == None:
    #     userinfo = client.get_user_info(openid)
    #     cache.set(openid, userinfo, 600)
    #   return JsonResponse({"code": 0, "message": "", "data": userinfo})