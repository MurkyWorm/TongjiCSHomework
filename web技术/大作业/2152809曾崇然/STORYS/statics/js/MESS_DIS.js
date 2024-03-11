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
            var url = '/INTERACT/mess_dis2/?order=' + order.innerText;
            axios.get(url)
            .then(response => {
                this.objects = response.data;
            })
            .catch(error => {
                console.error(error);
            });
        }
    }
});
card.mount('#card');