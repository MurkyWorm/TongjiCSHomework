from django.urls import path
from . import views

urlpatterns = [
    path('', views.info_ini),
    path('edit_name/', views.edit_name),
    path('edit_age/', views.edit_age),
    path('edit_gender/', views.edit_gender),
    path('edit_nature/', views.edit_nature),
    path('edit_pwd/', views.edit_pwd),
    path('edit_email/', views.edit_email),
    path('edit_pp/', views.edit_pp),
]