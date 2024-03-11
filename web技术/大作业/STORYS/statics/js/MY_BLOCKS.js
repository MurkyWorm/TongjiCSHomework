const user_name = document.getElementById('user_name');
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
            url = '/HOME/user_articles?user_name=' + user_name.innerText;
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
const Return = document.getElementById('Return');

Return.addEventListener('click', function () {
    window.location.href = '/HOME/?choice=all&value=1';
});

const intervalId = setInterval(function() {
    const card_parent = document.getElementsByClassName('card_parent');
    console.log(card_parent.length);
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
                else if (event.target.className == 'fas fa-edit child-element float-end') {
                    window.location.href = "/INTERACT/edit_idea?id=" + p_child.innerText;
                }
                else if (event.target.className == 'fas fa-trash-alt child-element float-end') {
                    window.location.href = "/INTERACT/delete_idea?id=" + p_child.innerText;
                }
                else if (event.target.className == 'far fa-bookmark') {
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
                            event.target.style.color = 'green';
                        }
                        else {
                            event.target.style.color = 'black';
                        }
                    })
                    .catch(error => {
                        console.error(error);
                    });
                }
                else {
                    var url = '/INTERACT/look_creation/?id=';
                    url = url + p_child.innerText;
                    window.location.href = url;
                }
            });
        }
        clearInterval(intervalId);
    }
}, 100);