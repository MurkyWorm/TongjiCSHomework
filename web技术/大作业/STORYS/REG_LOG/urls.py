from django.urls import path
from . import views

urlpatterns = [
    path('reg/', views.reg),
    path('reg_in/', views.reg_in),
    path('log/', views.log),
    path('log_in/', views.log_in),
    path('find_pwd/', views.find_pwd),
]