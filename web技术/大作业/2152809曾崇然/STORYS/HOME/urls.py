from django.urls import path
from . import views

urlpatterns = [
    path('', views.home_user),
    path('home_articles/', views.home_articles),
    path('home_exit/', views.home_exit),
    path('user_articles/', views.user_articles),
    path('my_blocks_user/', views.my_blocks_user),
]