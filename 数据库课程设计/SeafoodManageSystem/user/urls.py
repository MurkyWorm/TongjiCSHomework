from django.contrib import admin
from django.urls import path

from . import views

urlpatterns = [
    path('login/', views.login),
    path('register/', views.register),
    path('logout/', views.logout),
]