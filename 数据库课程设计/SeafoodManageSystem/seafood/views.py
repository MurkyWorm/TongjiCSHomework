from django.shortcuts import render, get_object_or_404
from .models import Product
from user.models import User
from django.core.serializers import serialize
import json
from django.utils import timezone
from datetime import timedelta, datetime
from home.models import Notice, OceanNuclearPollution

def foodpage(request):
    if request.session.get('is_login', None):
        user_name = request.session['user_name']
        user = User.objects.get(user_name=user_name)
        identity = user.identity
    else:
        identity = 0
    
    response_data = Product.objects.filter().order_by('-production_time')[:300]
    response_data = serialize('json', response_data, fields=('class_name', 'quantity', 'lat', 'lng', 'production_time', 'expiration_time', 'state'))
    response_data = json.loads(response_data)
    response_data = [{'product_id': item['pk'], **item['fields']} for item in response_data]
    response_data = json.dumps(response_data)

    return render(request, 'foodpage.html', {'response_data': response_data, 'identity': identity})

def filter_seafood(request):
    if request.session.get('is_login', None):
        user_name = request.session['user_name']
        user = User.objects.get(user_name=user_name)
        identity = user.identity
    else:
        identity = 0
    
    product_type = request.POST.get('productType')
    statusFilter = request.POST.get('statusFilter')
    timeFilter = request.POST.get('timeFilter')

    response_data = Product.objects.filter(class_name__icontains=product_type).order_by('-production_time')

    if statusFilter == '全部':
        pass
    elif statusFilter == '已售出':
        response_data = response_data.filter(state=1)
    else:
        response_data = response_data.filter(state=0)
    
    today = timezone.now().date()
    if timeFilter == '全部':
        pass
    elif timeFilter == '今天':
        response_data = response_data.filter(production_time__date=today)
    elif timeFilter == '本周':
        start_of_week = today - timedelta(days=today.weekday())
        end_of_week = start_of_week + timedelta(days=6)
        response_data = response_data.filter(production_time__date__range=[start_of_week, end_of_week])
    elif timeFilter == '本月':
        start_of_month = today.replace(day=1)
        end_of_month = today.replace(day=28) + timedelta(days=4)
        end_of_month = end_of_month - timedelta(days=end_of_month.day)
        response_data = response_data.filter(production_time__date__range=[start_of_month, end_of_month])
    else:
        start_of_year = today.replace(month=1, day=1)
        end_of_year = today.replace(month=12, day=31)
        response_data = response_data.filter(production_time__date__range=[start_of_year, end_of_year])
    
    response_data = response_data.filter()[:300]
    response_data = serialize('json', response_data, fields=('class_name', 'quantity', 'lat', 'lng', 'production_time', 'expiration_time', 'state'))
    response_data = json.loads(response_data)
    response_data = [{'product_id': item['pk'], **item['fields']} for item in response_data]
    response_data = json.dumps(response_data)

    return render(request, 'foodpage.html', {'response_data': response_data, 'identity': identity})


def product_detail(request, product_id):
    if request.session.get('is_login', None):
        user_name = request.session['user_name']
        user = User.objects.get(user_name=user_name)
        identity = user.identity
    else:
        identity = 0

    product = get_object_or_404(Product, pk=product_id)

    lat = product.lat
    lng = product.lng
    lat = int(float(lat) / 2) * 2
    lng = int(float(lng) / 2) * 2
    radiation = OceanNuclearPollution.objects.filter(lat=lat, lng=lng).order_by('-date')[:10].values('count', 'date')
    radiation = list(radiation)
    radiation.reverse()
    return render(request, 'product.html', {'product': product, 'identity': identity, 'radiation': radiation})