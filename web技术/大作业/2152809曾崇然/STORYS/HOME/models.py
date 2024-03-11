from django.db import models

# Create your models here.
class User_info(models.Model):
    user_name = models.CharField(max_length=20)
    user_pp = models.CharField(max_length=25)
    user_ideas = models.IntegerField()
    user_echo = models.IntegerField()
    user_fan = models.IntegerField()
    user_like = models.IntegerField()
    user_reply = models.IntegerField(default=0)
    user_concen = models.IntegerField()
    user_coll = models.IntegerField()
    user_generate = models.IntegerField()
    user_gender = models.CharField(max_length=20)
    user_age = models.IntegerField()
    user_nature = models.CharField(max_length=20)
    user_prefer = models.CharField(max_length=20)