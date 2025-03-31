from django.shortcuts import render, redirect
from . import models
from user.myforms import UserForm, RegisterForm
import hashlib


def hash_code(s, salt='Covid-19'):
    h = hashlib.sha256()
    s += salt
    h.update(s.encode())
    return h.hexdigest()


def login(request):
    if request.session.get('is_login', None):
        return redirect('/home/homepage')

    if request.method == "POST":
        login_form = UserForm(request.POST)
        message = "请检查填写的内容！"
        if login_form.is_valid():
            user_name = login_form.cleaned_data['user_name']
            password = login_form.cleaned_data['password']
            try:
                user = models.User.objects.get(user_name=user_name)
                if user.password == hash_code(password):
                    request.session['is_login'] = True
                    request.session['user_id'] = user.user_id
                    request.session['user_name'] = user.user_name
                    return redirect('/home/homepage')
                else:
                    message = "用户名或密码不正确！"
            except:
                message = "用户不存在！"
        return render(request, 'login.html', locals())
    login_form = UserForm()
    return render(request, 'login.html', locals())


def register(request):
    if request.session.get('is_login', None):
        return redirect("/home/homepage")
    if request.method == "POST":
        register_form = RegisterForm(request.POST)
        message = "请检查填写的内容！"
        if register_form.is_valid(): 
            user_name = register_form.cleaned_data['user_name']
            password1 = register_form.cleaned_data['password1']
            password2 = register_form.cleaned_data['password2']
            email = register_form.cleaned_data['email']
            if password1 != password2:
                message = "两次输入的密码不同！"
                return render(request, 'register.html', locals())
            else:
                same_name_user = models.User.objects.filter(user_name=user_name)
                if same_name_user:
                    message = '用户名已经存在！'
                    return render(request, 'register.html', locals())
                same_email_user = models.User.objects.filter(email=email)
                if same_email_user: 
                    message = '该邮箱地址已被注册！'
                    return render(request, 'register.html', locals())
                new_user = models.User.objects.create()
                new_user.user_name = user_name
                new_user.password = hash_code(password1) 
                new_user.email = email
                new_user.identity = 0
                new_user.save()
                return redirect('/user/login/') 
    register_form = RegisterForm()
    return render(request, 'register.html', locals())


def logout(request):
    if not request.session.get('is_login', None): 
        return redirect("/home/homepage")
    request.session.flush() 
    return redirect('/home/homepage')