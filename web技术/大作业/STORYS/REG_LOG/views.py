from django.shortcuts import render
from REG_LOG.models import Users
from HOME.models import User_info
import re
from django.db.models import Q
from django.http import HttpResponseRedirect
from django.views.decorators.csrf import csrf_protect

@csrf_protect
# Create your views here.
def reg(request):
    reg_data = {}
    reg_data['title'] = '注&nbsp;&nbsp;册&nbsp;&nbsp;账&nbsp;&nbsp;户'
    return render(request, './REG.html', reg_data)

def reg_in(request):
    if request.POST:
        reg_data = {}
        flag = 1
        # 验证昵称
        if len(request.POST['user_name']) == 0:
            flag = 0
            reg_data['name_err'] = '昵称不能为空'
        elif len(request.POST['user_name']) >= 20:
            flag = 0
            reg_data['name_err'] = '昵称过长'
        else:
            already = Users.objects.filter(user_name=request.POST['user_name']).count()
            if already == 1:
                flag = 0
                reg_data['name_err'] = '该昵称已注册'
        # 验证密码
        if len(request.POST['user_pwd']) == 0:
            flag = 0
            reg_data['pwd_err'] = '密码不能为空'
        elif len(request.POST['user_pwd']) > 0 and len(request.POST['user_pwd']) < 8:
            flag = 0
            reg_data['pwd_err'] = '密码过短'
        elif len(request.POST['user_pwd']) > 16:
            flag = 0
            reg_data['pwd_err'] = '密码过长'
        else:
            if not request.POST['user_pwd'].isalnum():
                flag = 0
                reg_data['pwd_err'] = '密码格式不正确'
        if len(request.POST['user_pwd2']) == 0:
            flag = 0
            reg_data['pwd2_err'] = '重复密码不能为空'
        else:
            if request.POST['user_pwd'] != request.POST['user_pwd2']:
                flag = 0
                reg_data['pwd2_err'] = '两次输入的密码不一致'
        # 验证邮箱
        if len(request.POST['user_email']) == 0:
            flag = 0
            reg_data['email_err'] = '邮箱不能为空'
        pattern = r'^[\w\.-]+@[\w\.-]+\.\w+$'
        match = re.match(pattern, request.POST['user_email'])
        if not bool(match):
            flag = 0
            reg_data['email_err'] = '邮箱格式不正确'
        # 验证电影、歌曲、小说
        if len(request.POST['favor_movie']) == 0:
            flag = 0
            reg_data['movie_err'] = '电影不能为空'
        elif len(request.POST['favor_movie']) >= 100:
            flag = 0
            reg_data['movie_err'] = '电影名称过长'
        if len(request.POST['favor_novel']) == 0:
            flag = 0
            reg_data['novel_err'] = '小说不能为空'
        elif len(request.POST['favor_novel']) >= 100:
            flag = 0
            reg_data['novel_err'] = '小说名称过长'
        if len(request.POST['favor_song']) == 0:
            flag = 0
            reg_data['song_err'] = '歌曲不能为空'
        elif len(request.POST['favor_song']) >= 100:
            flag = 0
            reg_data['song_err'] = '歌曲名称过长'

        if flag == 1:
            user = Users(user_name=request.POST['user_name'], user_password=request.POST['user_pwd'],
                        user_email=request.POST['user_email'], favor_movie=request.POST['favor_movie'],
                        favor_novel=request.POST['favor_novel'], favor_song=request.POST['favor_song'],
                        admin_right='0000')
            user.save()
            user_info = User_info(user_name=request.POST['user_name'], user_pp='initial', user_ideas=0,
                                  user_echo=0, user_fan=0, user_like=0, user_reply=0,user_concen=0,
                                  user_coll=0, user_generate=0, user_gender="未设置", user_age=0, user_nature="未设置",
                                  user_prefer="未设置")
            user_info.save()
            reg_data['title'] = '注&nbsp;&nbsp;册&nbsp;&nbsp;成&nbsp;&nbsp;功'
        else:
            reg_data['title'] = '注&nbsp;&nbsp;册&nbsp;&nbsp;失&nbsp;&nbsp;败'
        reg_data['user_name'] = request.POST['user_name']
        reg_data['user_pwd'] = request.POST['user_pwd']
        reg_data['user_pwd2'] = request.POST['user_pwd2']
        reg_data['user_email'] = request.POST['user_email']
        reg_data['favor_movie'] = request.POST['favor_movie']
        reg_data['favor_novel'] = request.POST['favor_novel']
        reg_data['favor_song'] = request.POST['favor_song']
        return render(request, './REG.html', reg_data)

def log(request):
    log_data = {}
    log_data['title'] = '登&nbsp;&nbsp;录&nbsp;&nbsp;账&nbsp;&nbsp;户'
    log_data['is_collapsed'] = False
    return render(request, './LOG.html', log_data)

def log_in(request):
    if request.POST:
        reg_data = {}
        flag = 1
        if request.POST['is_collapsed'] == 'True':
            reg_data['is_collapsed'] = True
        else:
            reg_data['is_collapsed'] = False
        # 验证昵称
        if len(request.POST['user_name']) == 0:
            flag = 0
            reg_data['name_err'] = '昵称不能为空'
        # 验证密码
        if len(request.POST['user_pwd']) == 0:
            flag = 0
            reg_data['pwd_err'] = '密码不能为空'
        if flag == 0:
            reg_data['title'] = '登&nbsp;&nbsp;录&nbsp;&nbsp;失&nbsp;&nbsp;败'
            reg_data['user_name'] = request.POST['user_name']
            reg_data['user_pwd'] = request.POST['user_pwd']
            return render(request, './LOG.html', reg_data)
        else:
            user = Users.objects.filter(Q(user_name=request.POST['user_name'])&Q(user_password=request.POST['user_pwd']))
            if user.count() == 1:
                if user.first().admin_right == '1111':
                    reg_data['title'] = '账&nbsp;&nbsp;号&nbsp;&nbsp;封&nbsp;&nbsp;禁'
                    reg_data['user_name'] = request.POST['user_name']
                    reg_data['user_pwd'] = request.POST['user_pwd']
                    return render(request, './LOG.html', reg_data)
                else:
                    url = '/HOME/?choice=' + request.POST['choice'] + '&value=' +request.POST['value']
                    response = HttpResponseRedirect(url)
                    response.set_cookie('is_login', 'true', expires=3600)
                    user_name = request.POST['user_name']
                    user_name = user_name.encode("utf-8")
                    response.set_cookie('user_name', user_name, expires=3600)
                    return response
            else:
                reg_data['title'] = '登&nbsp;&nbsp;录&nbsp;&nbsp;失&nbsp;&nbsp;败'
                reg_data['pwd_err'] = '昵称或密码错误'
                reg_data['user_name'] = request.POST['user_name']
                reg_data['user_pwd'] = request.POST['user_pwd']
                return render(request, './LOG.html', reg_data)

def find_pwd(request):
    if request.POST:
        find_data = {}
        find_data['title'] = '登&nbsp;&nbsp;录&nbsp;&nbsp;账&nbsp;&nbsp;户'
        find_data['find_name'] = request.POST['find_name']
        find_data['find_movie'] = request.POST['find_movie']
        find_data['find_novel'] = request.POST['find_novel']
        find_data['find_song'] = request.POST['find_song']
        if request.POST['is_collapsed'] == 'True':
            find_data['is_collapsed'] = True
        else:
            find_data['is_collapsed'] = False
        user = Users.objects.filter(Q(user_name=request.POST['find_name'])&Q(favor_movie=request.POST['find_movie'])&Q(favor_novel=request.POST['find_novel'])&Q(favor_song=request.POST['find_song']))
        if user.count() == 1:
            find_data['find_pwd'] = '您的密码是：' + user.first().user_password
            return render(request, './LOG.html', find_data)
        else:
            find_data['song_err'] = '昵称或问题回答错误'
            return render(request, './LOG.html', find_data)