from django.db import models

class Notice(models.Model):
    notice_id = models.AutoField(primary_key=True)
    publisher = models.ForeignKey('user.User', on_delete=models.CASCADE, verbose_name="发布者")
    title = models.CharField(max_length=20, verbose_name="标题")
    content = models.TextField(max_length=500, verbose_name="内容")
    pic_url = models.CharField(max_length=100, verbose_name="图片链接")
    start_time = models.DateTimeField(verbose_name="开始时间")
    end_time = models.DateTimeField(verbose_name="结束时间")
    priority = models.IntegerField(verbose_name="优先级")

    def __str__(self):
        return self.title


class OceanNuclearPollution(models.Model):
    count = models.IntegerField(null=False)
    lat = models.FloatField(null=False)
    lng = models.FloatField(null=False)
    date = models.DateField(null=False)

    def __str__(self):
        return f"Pollution Event on {self.date} at ({self.lat}, {self.lng}) with count {self.count}"


