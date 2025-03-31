from django.urls import path

from . import views

urlpatterns = [
    path('helperpage/', views.helperpage),
    path('select/', views.select_info),
]