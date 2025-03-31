from django.db import models

# Create your models here.
class User(models.Model):
    user_id = models.AutoField(primary_key=True)
    identity = models.IntegerField(
        choices=((1, 'Type 1'), (2, 'Type 2'), (3, 'Type 3')),
        null=False,
        default=1
    )
    email = models.EmailField(max_length=50, null=False)
    user_name = models.CharField(max_length=50, null=False)
    password = models.CharField(max_length=500, null=False)

    def __str__(self):
        return self.user_name