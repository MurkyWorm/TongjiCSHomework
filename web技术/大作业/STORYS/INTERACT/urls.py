from django.urls import path
from . import views

urlpatterns = [
    path('add_idea/', views.add_idea),
    path('edit_idea/', views.edit_idea),
    path('save_idea/', views.save_idea),
    path('delete_idea/', views.delete_idea),
    path('publish_idea/', views.publish_idea),
    path('look_creation/', views.look_creation),
    path('add_like/', views.add_like),
    path('add_dislike/', views.add_dislike),
    path('add_coll/', views.add_coll),
    path('add_concen/', views.add_concen),
    path('send_comment/', views.send_comment),
    path('get_comments/', views.get_comments),
    path('add_likec/', views.add_likec),
    path('add_dislikec/', views.add_dislikec),
    path('mess_dis1/', views.mess_dis1),
    path('mess_dis2/', views.mess_dis2),
    path('message_show1/', views.message_show1),
    path('message_show2/', views.message_show2),
    path('message_check/', views.message_check),
    path('message_delete/', views.message_delete),
    path('report/', views.report),
]