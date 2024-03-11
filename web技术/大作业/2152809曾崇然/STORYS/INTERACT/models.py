from django.db import models
from django.contrib import admin

# Create your models here.
class Like(models.Model):
    user_name = models.CharField(max_length=20)
    target = models.CharField(max_length=20)
    type = models.CharField(max_length=20,default="创作")

class Clike(models.Model):
    user_name = models.CharField(max_length=20)
    target = models.CharField(max_length=20)

class Dislike(models.Model):
    user_name = models.CharField(max_length=20)
    target = models.CharField(max_length=20)
    type = models.CharField(max_length=20,default="创作")

class Cdislike(models.Model):
    user_name = models.CharField(max_length=20)
    target = models.CharField(max_length=20)

class Comment(models.Model):
    user_name = models.CharField(max_length=20)
    target = models.CharField(max_length=20)
    content = models.TextField()
    type = models.CharField(max_length=20, default="创作")
    like = models.IntegerField(default=0)
    dislike = models.IntegerField(default=0)

class Concen(models.Model):
    user_name = models.CharField(max_length=20)
    target = models.CharField(max_length=20)

class coll(models.Model):
    user_name = models.CharField(max_length=20)
    creation_name = models.CharField(max_length=100)

class Creation(models.Model):
    user_name = models.CharField(max_length=20)
    creation_id = models.IntegerField(default=0)
    title = models.TextField(default="")
    introd_cont = models.TextField()
    content = models.TextField()
    is_punish = models.CharField(max_length=10)
    look = models.IntegerField(default=0)
    like = models.IntegerField(default=0)
    dislike = models.IntegerField(default=0)
    comment = models.IntegerField(default=0)

class Message(models.Model):
    target = models.CharField(max_length=20,default="")
    content = models.TextField()
    is_read = models.CharField(max_length=10,default="未读")
    type = models.CharField(max_length=10, default="")

class Refer(models.Model):
    echo_id = models.CharField(max_length=20)
    refer_id = models.CharField(max_length=20)

class CreationAdmin(admin.ModelAdmin):
    list_display = ('id', )

admin.site.register(Creation, CreationAdmin)
