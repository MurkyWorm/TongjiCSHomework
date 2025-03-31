from captcha.fields import CaptchaField, CaptchaTextInput
from django import forms


class UserForm(forms.Form):
    user_name = forms.CharField(label="用户名", max_length=16, widget=forms.TextInput(attrs={'class': 'form-control'}))
    password = forms.CharField(label="密码", max_length=16, widget=forms.PasswordInput(attrs={'class': 'form-control'}))
    captcha = CaptchaField(label='验证码', widget=CaptchaTextInput(attrs={'class': 'form-control'}))


class RegisterForm(forms.Form):
    user_name = forms.CharField(label="用户名", max_length=16, widget=forms.TextInput(attrs={'class': 'form-control'}))
    password1 = forms.CharField(label="密码", max_length=16, widget=forms.PasswordInput(attrs={'class': 'form-control'}))
    password2 = forms.CharField(label="确认密码", max_length=16, widget=forms.PasswordInput(attrs={'class': 'form-control'}))
    email = forms.EmailField(label="邮箱地址", widget=forms.EmailInput(attrs={'class': 'form-control'}))
    captcha = CaptchaField(label='验证码', widget=CaptchaTextInput(attrs={'class': 'form-control'}))