from django.db import models
from django.contrib import admin

# Create your models here.
class Users(models.Model):
    user_name = models.CharField(max_length = 20)
    user_password = models.CharField(max_length = 100)
    user_email = models.EmailField()
    favor_movie = models.CharField(max_length = 100)
    favor_novel = models.CharField(max_length=100)
    favor_song = models.CharField(max_length=100)
    admin_right = models.CharField(max_length = 4)


class UsersAdmin(admin.ModelAdmin):
    list_display = ('user_name', )

admin.site.register(Users, UsersAdmin)