from django.shortcuts import render, HttpResponse
from django.http import JsonResponse
from datetime import datetime
from datetime import date
from .models import Notice, OceanNuclearPollution
from user.models import User
from django.core.serializers import serialize
import json

def homepage(request):
    if request.session.get('is_login', None):
        user_name = request.session['user_name']
        user = User.objects.get(user_name=user_name)
        identity = user.identity
    else:
        identity = 0
    now = datetime.now()
    active_notices = Notice.objects.filter(end_time__gt=now).order_by('-priority')
    if active_notices.count() < 3:
        remaining_count = 3 - active_notices.count()
        additional_notices = Notice.objects.order_by('end_time')[:remaining_count]
        active_notices = list(active_notices) + list(additional_notices)
    
    today = date.today()
    radiation = OceanNuclearPollution.objects.filter(date=today)
    radiation = serialize('json', radiation, fields=('count', 'lat', 'lng'))
    radiation = [item['fields'] for item in json.loads(radiation)]
    radiation = json.dumps(radiation)

    return render(request, 'homepage.html', {'notices': active_notices[:3], 'identity': identity, 'radiation': radiation})


def changedate(request):
    if request.method != 'POST':
        return HttpResponse("This endpoint accepts only POST requests.", status=405)

    # 获取 POST 请求中的日期参数，如果没有提供则默认使用当前日期
    date_str = request.POST.get('date', datetime.now().strftime('%Y-%m-%d'))
    try:
        # 尝试将日期字符串转换为日期对象
        query_date = datetime.strptime(date_str, '%Y-%m-%d').date()
    except ValueError:
        # 如果日期格式不正确，返回错误消息
        return HttpResponse("Invalid date format. Please use YYYY-MM-DD.", status=400)

    # 用户身份检查
    if request.session.get('is_login', None):
        user_name = request.session['user_name']
        user = User.objects.get(user_name=user_name)
        identity = user.identity
    else:
        identity = 0

    # 根据提供的日期查询辐射信息
    radiation = OceanNuclearPollution.objects.filter(date=query_date)
    radiation_json = serialize('json', radiation, fields=('count', 'lat', 'lng'))
    radiation_data = [item['fields'] for item in json.loads(radiation_json)]

    # 创建HTTP响应，返回JSON数据
    response_data = {
        'identity': identity,
        'radiation': radiation_data
    }
    return HttpResponse(json.dumps(response_data), content_type="application/json")


def changelocation(request):
    if request.method != 'POST':
        return HttpResponse("This endpoint accepts only POST requests.", status=405)
    lat = request.POST.get('latitude', 0)
    lng = request.POST.get('longitude', 0)
    lat = int(float(lat) / 2) * 2
    lng = int(float(lng) / 2) * 2
    response_data = OceanNuclearPollution.objects.filter(lat=lat, lng=lng).order_by('-date')[:10].values('count', 'date')
    response_data = list(response_data)
    response_data.reverse()
    return JsonResponse(response_data, safe=False)



def test(request):
    return render(request, 'test.html')