from django.shortcuts import render
from HOME.models import User_info
from REG_LOG.models import Users
from INTERACT.models import Like, Clike, Dislike, Cdislike, Comment, Concen, coll, Creation
from django.http import HttpResponseRedirect
from django.forms.models import model_to_dict
from django.http import JsonResponse
from django.db.models import Q
import re
from django.http import HttpResponseBadRequest
from django.utils.http import urlencode
from django.views.decorators.csrf import csrf_protect

@csrf_protect
# Create your views here.

def info_ini(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            user_info1 = User_info.objects.filter(id=request.GET['user_id']).first()
            user_info = model_to_dict(user_info1)
            user_info2 = Users.objects.filter(user_name=user_info1.user_name).first()
            user_data = {}
            user_data['id'] = user_info['id']
            user_data['user_pp'] = user_info['user_pp'] + '.jpg'
            user_data['user_name'] = user_info['user_name']
            user_data['user_gender'] = user_info['user_gender']
            user_data['user_age'] = user_info['user_age']
            user_data['user_nature'] = user_info['user_nature']
            user_data['user_prefer'] = user_info['user_prefer']
            user_data['user_email'] = user_info2.user_email
            return render(request, './PER_INFO.html', user_data)
    else:
        return HttpResponseRedirect('/REG_LOG/log')

def edit_name(request):
    data = {}
    flag = 1
    if len(request.GET['new_name']) >= 20:
        flag = 0
        data['result'] = '昵称过长'
    else:
        already = Users.objects.filter(user_name=request.GET['new_name']).count()
        if already == 1:
            flag = 0
            data['result'] = '该昵称已注册'
    if flag == 1:
        user_info = User_info.objects.filter(id=request.GET['id']).first()
        old_name = user_info.user_name
        user_info.user_name = request.GET['new_name']
        user_info.save()
        user = Users.objects.filter(user_name=old_name).first()
        user.user_name = request.GET['new_name']
        user.save()
        likes = Like.objects.filter(user_name=old_name)
        for like in likes:
            like.user_name = request.GET['new_name']
            like.save()
        clikes = Clike.objects.filter(user_name=old_name)
        for clike in clikes:
            clike.user_name = request.GET['new_name']
            clike.save()
        dislikes = Dislike.objects.filter(user_name=old_name)
        for dislike in dislikes:
            dislike.user_name = request.GET['new_name']
            dislike.save()
        cdislikes = Cdislike.objects.filter(user_name=old_name)
        for cdislike in cdislikes:
            cdislike.user_name = request.GET['new_name']
            cdislike.save()
        comments = Comment.objects.filter(user_name=old_name)
        for comment in comments:
            comment.user_name = request.GET['new_name']
            comment.save()
        concens = Concen.objects.filter(Q(user_name=old_name) | Q(target=old_name))
        for concen in concens:
            if concen.user_name == old_name:
                concen.user_name = request.GET['new_name']
            if concen.target == old_name:
                concen.target = request.GET['new_name']
            concen.save()
        colls = coll.objects.filter(user_name=old_name)
        for coll1 in colls:
            coll1.user_name = request.GET['new_name']
            coll1.save()
        creations = Creation.objects.filter(user_name=old_name)
        for creation in creations:
            creation.user_name = request.GET['new_name']
            creation.save()
        data['result'] = '修改成功,马上跳转到登录界面'
        response = HttpResponseRedirect('/REG_LOG/log')
        response.set_cookie('is_login', 'false', expires='Thu, 01 Jan 1970 00:00:00 GMT')
    return JsonResponse(data, safe=False)

def edit_gender(request):
    data = {}
    flag = 1
    if len(request.GET['new_gender']) >= 20:
        flag = 0
        data['result'] = '性别过长'
    if flag == 1:
        user_info = User_info.objects.filter(id=request.GET['id']).first()
        user_info.user_gender = request.GET['new_gender']
        user_info.save()
        data['result'] = '修改成功'
    return JsonResponse(data, safe=False)

def edit_age(request):
    data = {}
    if request.GET['new_age'].isdigit():
        user_info = User_info.objects.filter(id=request.GET['id']).first()
        user_info.user_age = request.GET['new_age']
        user_info.save()
        data['result'] = '修改成功'
    else:
        data['result'] = '格式不正确'
    return JsonResponse(data, safe=False)

def edit_nature(request):
    data = {}
    if len(request.GET['new_nature']) >= 20:
        data['result'] = '性格过长'
    else:
        user_info = User_info.objects.filter(id=request.GET['id']).first()
        user_info.user_nature = request.GET['new_nature']
        user_info.save()
        data['result'] = '修改成功'
    return JsonResponse(data, safe=False)

def edit_pwd(request):
    data = {}
    flag = 1
    parts = request.GET['new_pwd'].split('*')
    if len(parts) != 2:
        print(request.GET['new_pwd'])
        print(len(parts))
        print(parts)
        data['result'] = '格式错误'
        return JsonResponse(data, safe=False)
    Old_pwd = parts[0]
    New_pwd = parts[1]
    user_info = User_info.objects.filter(id=request.GET['id']).first()
    user = Users.objects.filter(Q(user_name=user_info.user_name) & Q(user_password=Old_pwd))
    if user.count() == 0:
        flag = 0
        data['result'] = '原密码错误'
    else:
        if len(New_pwd) == 0:
            flag = 0
            data['result'] = '新密码不能为空'
        elif len(New_pwd) > 0 and len(New_pwd) < 8:
            flag = 0
            data['result'] = '新密码过短'
        elif len(New_pwd) > 16:
            flag = 0
            data['result'] = '新密码过长'
        else:
            if not New_pwd.isalnum():
                flag = 0
                data['result'] = '新密码格式不正确'
    if flag == 1:
        u = user.first()
        u.user_password = New_pwd
        u.save()
        data['result'] = '修改成功,马上跳转到登录页面'
    return JsonResponse(data, safe=False)

def edit_email(request):
    data = {}
    pattern = r'^[\w\.-]+@[\w\.-]+\.\w+$'
    match = re.match(pattern, request.GET['new_email'])
    if not bool(match):
        data['result'] = '邮箱格式不正确'
    else:
        user_info = User_info.objects.filter(id=request.GET['id']).first()
        user = Users.objects.filter(user_name=user_info.user_name).first()
        user.user_email = request.GET['new_email']
        data['result'] = '修改成功'
    return JsonResponse(data, safe=False)

def edit_pp(request):
    if request.method == 'POST' and request.FILES.get('file'):
        uploaded_file = request.FILES['file']
        allowed_extensions = ['jpg', 'jpeg']
        file_extension = uploaded_file.name.split('.')[-1].lower()
        if file_extension not in allowed_extensions:
            return HttpResponseBadRequest('只允许上传 JPG 文件。')
        max_size = 2 * 1024 * 1024  # 2MB
        if uploaded_file.size > max_size:
            return HttpResponseBadRequest('文件大小不能超过 2MB。')

        user_info = User_info.objects.filter(id=request.POST['user_id']).first()
        user_info.user_pp = 'pp_' + user_info.user_name
        user_info.save()
        save_path = 'statics/images/' + user_info.user_pp + '.jpg'
        with open(save_path, 'wb') as file:
            for chunk in uploaded_file.chunks():
                file.write(chunk)
        params = {}
        params['user_id'] = request.POST['user_id']
        query_string = urlencode(params)
        url = '/PER_INFO/'
        redirect_url = f'{url}?{query_string}'
        return HttpResponseRedirect(redirect_url)
    return HttpResponseBadRequest('无效的请求。')