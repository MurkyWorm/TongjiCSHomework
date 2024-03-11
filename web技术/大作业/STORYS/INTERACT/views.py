from django.shortcuts import render
from django.http import JsonResponse
from django.http import HttpResponseRedirect
from .models import Like, Dislike, Comment, Concen, coll, Creation, Clike, Cdislike, Message
from HOME.models import User_info
from REG_LOG.models import Users
from django.forms.models import model_to_dict
import ast
from django.db.models import Q
from django.views.decorators.csrf import csrf_protect

@csrf_protect
# Create your views here.

def add_idea(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            user_info1 = User_info.objects.filter(user_name=decoded_name).first()
            user_info1.user_ideas = user_info1.user_ideas + 1
            user_info1.save()
            creation = Creation(user_name=decoded_name, introd_cont="", content="", is_punish="未发布", creation_id=user_info1.user_ideas)
            creation.save()
            user_info = model_to_dict(user_info1)
            user_data = {}
            user_data['user_pp'] = user_info['user_pp'] + '.jpg'
            user_data['user_name'] = user_info['user_name']
            user_data['creation_id'] = user_info1.user_ideas
            return render(request, './CREATION.html', user_data)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def edit_idea(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            user_info1 = User_info.objects.filter(user_name=decoded_name).first()
            user_info = model_to_dict(user_info1)
            creation_data = {}
            creation_data['user_pp'] = user_info['user_pp'] + '.jpg'
            creation_data['user_name'] = user_info['user_name']
            creation_data['creation_id'] = user_info1.user_ideas
            creation = Creation.objects.filter(id=request.GET['id']).first()
            creation_data['title'] = creation.title
            creation_data['introd'] = creation.introd_cont
            creation_data['content'] = creation.content
            return render(request, './CREATION.html', creation_data)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def delete_idea(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            creation = Creation.objects.filter(id=request.GET['id']).first()
            creation.delete()
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            user_info = User_info.objects.filter(user_name=decoded_name).first()
            user_info.user_ideas = user_info.user_ideas - 1
            user_info.save()
            return HttpResponseRedirect('/HOME/my_blocks_user/')
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def save_idea(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            creation = Creation.objects.filter(Q(user_name=decoded_name) & Q(creation_id=request.POST['p_creation_id'])).first()
            creation.introd_cont = request.POST['p_introd']
            creation.title = request.POST['p_title']
            creation.content = request.POST['p_content']
            creation.save()
            result = ['保存成功']
            return JsonResponse(result, safe=False)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def publish_idea(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            creation = Creation.objects.filter(Q(user_name=decoded_name) & Q(creation_id=request.POST['p_creation_id'])).first()
            creation.is_punish = '已发布'
            creation.save()
            result = ['保存成功']
            return JsonResponse(result, safe=False)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def look_creation(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            creation = Creation.objects.filter(id=request.GET['id']).first()
            creation.look = creation.look + 1
            creation.save()
            creation_data = {}
            creation_data['user_name'] = creation.user_name
            creation_data['title'] = creation.title
            creation_data['introd'] = creation.introd_cont
            creation_data['content'] = creation.content
            creation_data['creation_id'] = request.GET['id']
            user = User_info.objects.filter(user_name=creation.user_name).first()
            creation_data['user_pp'] = user.user_pp + '.jpg'
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            likes = Like.objects.filter(Q(target=request.GET['id']) & Q(user_name=decoded_name))
            if likes.count() == 0:
                creation_data['like'] = 'white'
            else:
                creation_data['like'] = '#aaaaaa'
            dislikes = Dislike.objects.filter(Q(target=request.GET['id']) & Q(user_name=decoded_name))
            if dislikes.count() == 0:
                creation_data['dislike'] = 'white'
            else:
                creation_data['dislike'] = '#aaaaaa'
            colls = coll.objects.filter(Q(creation_name=request.GET['id']) & Q(user_name=decoded_name))
            if colls.count() == 0:
                creation_data['coll'] = 'white'
            else:
                creation_data['coll'] = '#aaaaaa'
            concens = Concen.objects.filter(Q(target=creation.user_name) & Q(user_name=decoded_name))
            if concens.count() == 0:
                creation_data['concen'] = 'white'
            else:
                creation_data['concen'] = '#aaaaaa'
            return render(request, './READ.html', creation_data)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def add_like(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            data = {}
            creation = Creation.objects.filter(id=request.POST['id']).first()
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            likes = Like.objects.filter(Q(target=request.POST['id']) & Q(user_name=decoded_name))
            author = User_info.objects.filter(user_name=creation.user_name).first()
            if likes.count() == 0:
                creation.like = creation.like + 1
                like = Like(user_name=decoded_name, target=request.POST['id'])
                like.save()
                author.user_like = author.user_like + 1
                author.save()
                data['result'] = '点赞成功'
                m_cont = decoded_name + " 赞了你的博客 《" + creation.title +"》 "
                message = Message(target=author.id, content=m_cont, is_read="未读", type="like")
                message.save()
            else:
                creation.like = creation.like - 1
                likes.first().delete()
                author.user_like = author.user_like - 1
                author.save()
                data['result'] = '取消点赞'
            creation.save()
            return JsonResponse(data, safe=False)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def add_dislike(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            data = {}
            creation = Creation.objects.filter(id=request.POST['id']).first()
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            dislikes = Dislike.objects.filter(Q(target=request.POST['id']) & Q(user_name=decoded_name))
            if dislikes.count() == 0:
                creation.dislike = creation.dislike + 1
                dislike = Dislike(user_name=decoded_name, target=request.POST['id'])
                dislike.save()
                data['result'] = '点踩成功'
            else:
                creation.dislike = creation.dislike - 1
                dislikes.first().delete()
                data['result'] = '取消点踩'
            creation.save()
            return JsonResponse(data, safe=False)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def add_coll(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            data = {}
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            colls = coll.objects.filter(Q(creation_name=request.POST['id']) & Q(user_name=decoded_name))
            user = User_info.objects.filter(user_name=decoded_name).first()
            if colls.count() == 0:
                co = coll(user_name=decoded_name, creation_name=request.POST['id'])
                co.save()
                user.user_coll = user.user_coll + 1
                user.save()
                data['result'] = '收藏成功'
            else:
                colls.first().delete()
                user.user_coll = user.user_coll - 1
                user.save()
                data['result'] = '取消收藏'
            return JsonResponse(data, safe=False)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def add_concen(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            data = {}
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            concens = Concen.objects.filter(Q(target=request.POST['creator']) & Q(user_name=decoded_name))
            user = User_info.objects.filter(user_name=decoded_name).first()
            author = User_info.objects.filter(user_name=request.POST['creator']).first()
            if concens.count() == 0:
                concen = Concen(user_name=decoded_name, target=request.POST['creator'])
                concen.save()
                user.user_concen = user.user_concen + 1
                user.save()
                author.user_fan = author.user_fan + 1
                author.save()
                data['result'] = '关注成功'
            else:
                concens.first().delete()
                user.user_concen = user.user_concen - 1
                user.save()
                author.user_fan = author.user_fan - 1
                author.save()
                data['result'] = '取消关注'
            return JsonResponse(data, safe=False)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def send_comment(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            data = {}
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            comment = Comment(user_name=decoded_name, target=request.POST['creation_id'], content=request.POST['cc'])
            comment.save()
            creation = Creation.objects.filter(id=request.POST['creation_id']).first()
            creation.comment = creation.comment + 1
            creation.save()
            author = User_info.objects.filter(user_name=creation.user_name).first()
            author.user_reply = author.user_reply + 1
            author.save()
            m_cont = decoded_name + " 评论了你的博客 《" + creation.title + "》 :" + request.POST['cc']
            message = Message(target=author.id, content=m_cont, is_read="未读", type="comment")
            message.save()
            data['result'] = '评论成功'
            return JsonResponse(data, safe=False)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def get_comments(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            comments = Comment.objects.filter(target=request.GET['creation_id'])
            comments_data = []
            for comment in comments:
                mid = ['', '', '', '', '', '', '']
                mid[0] = comment.user_name
                mid[1] = comment.content
                mid[2] = comment.like
                mid[3] = comment.dislike
                mid[4] = comment.id
                clikes = Clike.objects.filter(Q(target=comment.id) & Q(user_name=decoded_name))
                if clikes.count() == 0:
                    mid[5] = 'black'
                else:
                    mid[5] = 'green'
                dislikes = Cdislike.objects.filter(Q(target=comment.id) & Q(user_name=decoded_name))
                if dislikes.count() == 0:
                    mid[6] = 'black'
                else:
                    mid[6] = 'red'
                comments_data.append(mid)
            return JsonResponse(comments_data, safe=False)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def add_likec(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            data = {}
            comment = Comment.objects.filter(id=request.POST['id']).first()
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            clikes = Clike.objects.filter(Q(target=request.POST['id']) & Q(user_name=decoded_name))
            if clikes.count() == 0:
                comment.like = comment.like + 1
                clike = Clike(user_name=decoded_name, target=request.POST['id'])
                clike.save()
                data['result'] = '点赞成功'
            else:
                comment.like = comment.like - 1
                clikes.first().delete()
                data['result'] = '取消点赞'
            comment.save()
            return JsonResponse(data, safe=False)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def add_dislikec(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            data = {}
            comment = Comment.objects.filter(id=request.POST['id']).first()
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            cdislikes = Cdislike.objects.filter(Q(target=request.POST['id']) & Q(user_name=decoded_name))
            if cdislikes.count() == 0:
                comment.dislike = comment.dislike + 1
                cdislike = Cdislike(user_name=decoded_name, target=request.POST['id'])
                cdislike.save()
                data['result'] = '点踩成功'
            else:
                comment.dislike = comment.dislike - 1
                cdislikes.first().delete()
                data['result'] = '取消点踩'
            comment.save()
            return JsonResponse(data, safe=False)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def mess_dis1(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            user_info1 = User_info.objects.filter(user_name=decoded_name).first()
            user_info = model_to_dict(user_info1)
            user_data = {}
            user_data['id'] = user_info['id']
            user_data['user_pp'] = user_info['user_pp'] + '.jpg'
            user_data['user_name'] = user_info['user_name']
            user_data['order'] = request.GET['order']
            return render(request, './MESS_DIS.html', user_data)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def mess_dis2(request):
    data = []
    decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
    if request.GET['order'] == 'my_fans':
        concens = Concen.objects.filter(target=decoded_name)
        for concen in concens:
            ob = concen.user_name
            data.append(ob)
    elif request.GET['order'] == 'my_likes':
        creations = Creation.objects.filter(user_name=decoded_name)
        for creation in creations:
            likes = Like.objects.filter(target=creation.id)
            for like in likes:
                ob = like.user_name + " 赞了你的博客 " + creation.title
                data.append(ob)
        comments =Comment.objects.filter(user_name=decoded_name)
        for comment in comments:
            clikes = Clike.objects.filter(target=comment.id)
            for clike in clikes:
                ob = clike.user_name + " 赞了你的评论 " + comment.content
                data.append(ob)
    elif request.GET['order'] == 'my_reply':
        creations = Creation.objects.filter(user_name=decoded_name)
        for creation in creations:
            comments = Comment.objects.filter(target=creation.id)
            for comment in comments:
                ob = comment.user_name + " 回复了你的博客 《" + creation.title + "》 :" + comment.content
                data.append(ob)
    elif request.GET['order'] == 'my_concen':
        concens = Concen.objects.filter(user_name=decoded_name)
        for concen in concens:
            ob = concen.target
            data.append(ob)
    return JsonResponse(data, safe=False)

def message_show1(request):
    if 'is_login' in request.COOKIES:
        if request.COOKIES['is_login'] == 'true':
            decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
            user_info1 = User_info.objects.filter(user_name=decoded_name).first()
            user_info = model_to_dict(user_info1)
            user_data = {}
            user_data['id'] = user_info['id']
            user_data['user_pp'] = user_info['user_pp'] + '.jpg'
            user_data['user_name'] = user_info['user_name']
            return render(request, './MESSAGE.html', user_data)
    else:
        return HttpResponseRedirect('/REG_LOG/log?choice=all&value=1')

def message_show2(request):
    decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
    user_info = User_info.objects.filter(user_name=decoded_name).first()
    messages1 = Message.objects.filter(Q(target=user_info.id) & Q(type='report') & Q(is_read='未读'))
    messages2 = Message.objects.filter(Q(target=user_info.id) & Q(type='comment') & Q(is_read='未读'))
    messages3 = Message.objects.filter(Q(target=user_info.id) & Q(type='like') & Q(is_read='未读'))
    messages4 = Message.objects.filter(Q(target=user_info.id) & Q(is_read='已读'))
    data = []
    for message in messages1:
        mid = ['', '', '']
        mid[0] = message.content
        mid[1] = message.is_read
        mid[2] = message.id
        data.append(mid)
    for message in messages2:
        mid = ['', '', '']
        mid[0] = message.content
        mid[1] = message.is_read
        mid[2] = message.id
        data.append(mid)
    for message in messages3:
        mid = ['', '', '']
        mid[0] = message.content
        mid[1] = message.is_read
        mid[2] = message.id
        data.append(mid)
    for message in messages4:
        mid = ['', '', '']
        mid[0] = message.content
        mid[1] = message.is_read
        mid[2] = message.id
        data.append(mid)
    return JsonResponse(data, safe=False)

def message_delete(request):
    message = Message.objects.filter(id=request.GET['id']).first()
    message.delete()
    data = []
    return JsonResponse(data, safe=False)

def message_check(request):
    message = Message.objects.filter(id=request.GET['id']).first()
    if message.is_read == '未读':
        message.is_read = '已读'
    else:
        message.is_read = '未读'
    message.save()
    data = []
    return JsonResponse(data, safe=False)

def report(request):
    decoded_name = ast.literal_eval(request.COOKIES['user_name']).decode("utf-8")
    creation = Creation.objects.filter(id=request.POST['id']).first()
    user = Users.objects.filter(admin_right='0001').first()
    user_info = User_info.objects.filter(user_name=user.user_name).first()
    data = {}
    m_cont = decoded_name + " 举报了 " + creation.user_name + " 的编号为" + request.POST['id'] + "的博客: " + request.POST['content']
    message = Message(target=user_info.id, content=m_cont, is_read="未读", type="report")
    message.save()
    data['result'] = '举报成功'
    return JsonResponse(data, safe=False)