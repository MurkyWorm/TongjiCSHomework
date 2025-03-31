from django.urls import path

from . import views

urlpatterns = [
    path('foodpage/', views.foodpage),
    path('filter/', views.filter_seafood),
    path('product/<int:product_id>/', views.product_detail)
]