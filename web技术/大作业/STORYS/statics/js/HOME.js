const choice = document.getElementById('choice');
const value = document.getElementById('value');
const card = Vue.createApp({
    data() {
        return {
            articles: []
        };
    },
    created() {
        this.get_articles();
    },
    methods: {
        get_articles() {
            var url = '/HOME/home_articles/?choice=' + choice.innerText + '&value=' + value.innerText;
            axios.get(url)
            .then(response => {
                this.articles = response.data;
            })
            .catch(error => {
                console.error(error);
            });
        }
    }
});
card.mount('#card');

const exit = document.getElementById('exit');
const per_info = document.getElementById('per_info');
const add_idea = document.getElementById('add_idea');
const user_name = document.getElementById('user_name');
const user_id = document.getElementById('user_id');
const my_blocks = document.getElementById('my_blocks');
const my_fans = document.getElementById('my_fans');
const my_likes = document.getElementById('my_likes');
const my_reply = document.getElementById('my_reply');
const my_concen = document.getElementById('my_concen');
const my_coll = document.getElementById('my_coll');
const search = document.getElementById('search');
const search_cont = document.getElementById('search_cont');
const message = document.getElementById('message');
const report_id = document.getElementById('report_id');

message.addEventListener('click', function () {
    var url = '/INTERACT/message_show1/'
    window.location.href = url;
});

search.addEventListener('click', function () {
    if (search_cont.value != "") {
        var url = '/HOME/?choice=search&value=' + search_cont.value;
        window.location.href = url;
    }
});

my_fans.addEventListener('click', function () {
	window.location.href = '/INTERACT/mess_dis1/?order=my_fans';
});

my_likes.addEventListener('click', function () {
	window.location.href = '/INTERACT/mess_dis1/?order=my_likes';
});

my_reply.addEventListener('click', function () {
	window.location.href = '/INTERACT/mess_dis1/?order=my_reply';
});

my_coll.addEventListener('click', function () {
	window.location.href = '/HOME/?choice=coll&value=1';
});

my_concen.addEventListener('click', function () {
	window.location.href = '/INTERACT/mess_dis1/?order=my_concen';
});

exit.addEventListener('click', function () {
	axios.get('/HOME/home_exit')
	.then(response => {
        window.location.href = '/REG_LOG/log';
    })
    .catch(error => {
        console.error(error);
    });
});

per_info.addEventListener('click', function () {
    url = '/PER_INFO/?user_id=' + user_id.innerText;
    console.log(url)
    window.location.href = '/PER_INFO/?user_id=' + user_id.innerText;
});

add_idea.addEventListener('click', function () {
    window.location.href = '/INTERACT/add_idea';
});

my_blocks.addEventListener('click', function () {
    window.location.href = '/HOME/my_blocks_user/';
});

const intervalId = setInterval(function() {
    const card_parent = document.getElementsByClassName('card_parent');
    if (card_parent.length > 0) {
        for (let i = 0; i < card_parent.length; i++) {
            card_parent[i].addEventListener('click', function (event) {
                const p_child = card_parent[i].querySelector('.p_child');
                if (event.target.classList.contains('fa-thumbs-up')) {
                    const data = new FormData();
                    data.append('id', p_child.innerText);
                    const csrftoken = document.querySelector('[name=csrfmiddlewaretoken]').value;
                    axios.defaults.headers.common['X-CSRFToken'] = csrftoken;
	                axios.post('/INTERACT/add_like/', data, {
	                    headers: {
                            'Content-Type': 'multipart/form-data',
                        },
                    })
	                .then(response => {
                        console.log(response.data);
                        if (response.data.result == '点赞成功') {
                            event.target.className = 'fas fa-thumbs-up'
                            var str = event.target.innerText.substring(1);
                            str = parseInt(str) + 1;
                            event.target.innerText = ':' + str;
                        }
                        else {
                            event.target.className = 'far fa-thumbs-up'
                            var str = event.target.innerText.substring(1);
                            str = parseInt(str) - 1;
                            event.target.innerText = ':' + str;
                        }
                    })
                    .catch(error => {
                        console.error(error);
                    });
                }
                else if (event.target.classList.contains('fa-thumbs-down')) {
                    const data = new FormData();
                    data.append('id', p_child.innerText);
                    const csrftoken = document.querySelector('[name=csrfmiddlewaretoken]').value;
                    axios.defaults.headers.common['X-CSRFToken'] = csrftoken;
	                axios.post('/INTERACT/add_dislike/', data, {
	                    headers: {
                            'Content-Type': 'multipart/form-data',
                        },
                    })
	                .then(response => {
                        console.log(response.data);
                        if (response.data.result == '点踩成功') {
                            event.target.className = 'fas fa-thumbs-down';
                            var str = event.target.innerText.substring(1);
                            str = parseInt(str) + 1;
                            event.target.innerText = ':' + str;
                        }
                        else {
                            event.target.className = 'far fa-thumbs-down';
                            var str = event.target.innerText.substring(1);
                            str = parseInt(str) - 1;
                            event.target.innerText = ':' + str;
                        }
                    })
                    .catch(error => {
                        console.error(error);
                    });
                }
                else if (event.target.classList.contains('fa-bookmark')) {
                    const data = new FormData();
                    data.append('id', p_child.innerText);
                    const csrftoken = document.querySelector('[name=csrfmiddlewaretoken]').value;
                    axios.defaults.headers.common['X-CSRFToken'] = csrftoken;
	                axios.post('/INTERACT/add_coll/', data, {
	                    headers: {
                            'Content-Type': 'multipart/form-data',
                        },
                    })
	                .then(response => {
                        console.log(response.data);
                        if (response.data.result == '收藏成功') {
                            event.target.className = 'fas fa-bookmark';
                        }
                        else {
                            event.target.className = 'far fa-bookmark';
                        }
                    })
                    .catch(error => {
                        console.error(error);
                    });
                }
                else if (event.target.className == 'fas fa-exclamation-triangle') {
                    report_id.innerText = p_child.innerText;
                }
                else {
                    var url = '/INTERACT/look_creation/?id=';
                    url = url + p_child.innerText;
                    window.location.href = url;
                }
            });
        }
        const report_title = document.getElementById('report_title');
        const report_content = document.getElementById('report_content');
        const report_button = document.getElementById('report_button');
        clearInterval(intervalId);
        report_button.addEventListener('click', function () {
            if (report_content.value != "") {
                const data = new FormData();
                data.append('id', report_id.innerText);
                data.append('content', report_content.value)
                const csrftoken = document.querySelector('[name=csrfmiddlewaretoken]').value;
                axios.defaults.headers.common['X-CSRFToken'] = csrftoken;
	            axios.post('/INTERACT/report/', data, {
	                headers: {
                        'Content-Type': 'multipart/form-data',
                    },
                })
	            .then(response => {
                    console.log(response.data);
                    report_title.innerText = response.data.result;
                    setTimeout(function() {
                        location.reload();
                    }, 2000);
                })
                .catch(error => {
                    console.error(error);
                });
            }
            console.log(url)
            window.location.href = '/PER_INFO/?user_id=' + user_id.innerText;
        });
    }
}, 100);