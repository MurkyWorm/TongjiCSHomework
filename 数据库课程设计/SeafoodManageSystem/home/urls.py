from django.urls import path

from . import views

urlpatterns = [
    path('homepage/', views.homepage),
    path('changedate/', views.changedate),
    path('changelocation/', views.changelocation),
]