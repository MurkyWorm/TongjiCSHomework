const like = document.getElementById('like');
const dislike = document.getElementById('dislike');
const collection = document.getElementById('collection');
const book = document.getElementById('book');
const creation_id = document.getElementById('creation_id');
const creator = document.getElementById('creator');
const send_comment = document.getElementById('send_comment');
const cc = document.getElementById('cc');
const myModal = document.getElementById('myModal');

const card = Vue.createApp({
    data() {
        return {
            comments: []
        };
    },
    created() {
        this.get_comments();
    },
    methods: {
        get_comments() {
            url = '/INTERACT/get_comments/?creation_id=';
            url = url + creation_id.innerText
            axios.get(url)
            .then(response => {
                this.comments = response.data;
            })
            .catch(error => {
                console.error(error);
            });
        }
    }
})
card.mount('#card');

like.addEventListener('click', function () {
    const data = new FormData();
    data.append('id', creation_id.innerText);
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
            like.style.color = '#aaaaaa';
        }
        else {
             like.style.color = 'white';
        }
    })
    .catch(error => {
        console.error(error);
    });
});

dislike.addEventListener('click', function () {
    const data = new FormData();
    data.append('id', creation_id.innerText);
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
            dislike.style.color = '#aaaaaa';
        }
        else {
             dislike.style.color = 'white';
        }
    })
    .catch(error => {
        console.error(error);
    });
});

collection.addEventListener('click', function () {
    const data = new FormData();
    data.append('id', creation_id.innerText);
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
            collection.style.color = '#aaaaaa';
        }
        else {
             collection.style.color = 'white';
        }
    })
    .catch(error => {
        console.error(error);
    });
});

book.addEventListener('click', function () {
    const data = new FormData();
    data.append('creator', creator.innerText);
    const csrftoken = document.querySelector('[name=csrfmiddlewaretoken]').value;
    axios.defaults.headers.common['X-CSRFToken'] = csrftoken;
	axios.post('/INTERACT/add_concen/', data, {
	    headers: {
            'Content-Type': 'multipart/form-data',
        },
    })
	.then(response => {
        console.log(response.data);
        if (response.data.result == '关注成功') {
            book.style.color = '#aaaaaa';
        }
        else {
             book.style.color = 'white';
        }
    })
    .catch(error => {
        console.error(error);
    });
});

send_comment.addEventListener('click', function () {
    if (cc.value != "") {
        const data = new FormData();
        data.append('creation_id', creation_id.innerText);
        data.append('cc', cc.value);
        cc.value = "";
        const csrftoken = document.querySelector('[name=csrfmiddlewaretoken]').value;
        axios.defaults.headers.common['X-CSRFToken'] = csrftoken;
	    axios.post('/INTERACT/send_comment/', data, {
	        headers: {
                'Content-Type': 'multipart/form-data',
            },
        })
	    .then(response => {
            console.log(response.data);
            var modalInstance = new bootstrap.Modal(myModal);
            modalInstance.show();
            setTimeout(function() {
                location.reload();
            }, 2000);
        })
        .catch(error => {
            console.error(error);
        });
    }
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
	                axios.post('/INTERACT/add_likec/', data, {
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
	                axios.post('/INTERACT/add_dislikec/', data, {
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
            });
        }
        clearInterval(intervalId);
    }
}, 100);
