# Generated by Django 4.2.2 on 2023-06-19 09:36

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('INTERACT', '0003_delete_user_inter'),
    ]

    operations = [
        migrations.AddField(
            model_name='creation',
            name='creation_id',
            field=models.IntegerField(default=0),
        ),
    ]
