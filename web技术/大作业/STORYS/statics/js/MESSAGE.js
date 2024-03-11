const order = document.getElementById('order');
const Return = document.getElementById('Return');
Return.addEventListener('click', function () {
    window.location.href = '/HOME/?choice=all&value=1';
});
const card = Vue.createApp({
    data() {
        return {
            objects: []
        };
    },
    created() {
        this.get_objects();
    },
    methods: {
        get_objects() {
            var url = '/INTERACT/message_show2/'
            axios.get(url)
            .then(response => {
                console.log(response.data)
                this.objects = response.data;
            })
            .catch(error => {
                console.error(error);
            });
        }
    }
});
card.mount('#card');

const intervalId = setInterval(function() {
    const checks = document.getElementsByClassName('check');
    const deletes = document.getElementsByClassName('delete');
    if (checks.length > 0 && deletes.length > 0) {
        for (let i = 0; i < checks.length; i++) {
            checks[i].addEventListener('click', function () {
                const p_child = checks[i].parentNode.querySelector('.id');
                console.log(p_child.innerText);
                var url = '/INTERACT/message_check/?id=' + p_child.innerText;
                axios.get(url)
                .then(response => {
                    console.log(response.data)
                    this.objects = response.data;
                    location.reload();
                })
                .catch(error => {
                    console.error(error);
                });
            });
            deletes[i].addEventListener('click', function () {
                const p_child = checks[i].parentNode.querySelector('.id');
                console.log(p_child.innerText);
                var url = '/INTERACT/message_delete/?id=' + p_child.innerText;
                axios.get(url)
                .then(response => {
                    console.log(response.data)
                    this.objects = response.data;
                    location.reload();
                })
                .catch(error => {
                    console.error(error);
                });
            });
        }
        clearInterval(intervalId);
    }
}, 100);