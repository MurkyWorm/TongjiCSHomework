const save = document.getElementById('save');
const publish = document.getElementById('publish');
const title = document.getElementById('title');
const introd = document.getElementById('introd');
const content = document.getElementById('content');
const creation_id = document.getElementById('creation_id');

save.addEventListener('click', function () {
    const data = new FormData();
    data.append('p_title', title.value);
    data.append('p_introd', introd.value);
    data.append('p_content', content.value);
    data.append('p_creation_id', creation_id.innerText);
    const csrftoken = document.querySelector('[name=csrfmiddlewaretoken]').value;
    axios.defaults.headers.common['X-CSRFToken'] = csrftoken;
	axios.post('/INTERACT/save_idea/', data, {
	    headers: {
            'Content-Type': 'multipart/form-data',
        },
    })
	.then(response => {
        console.log(response.data);
    })
    .catch(error => {
        console.error(error);
    });
});

publish.addEventListener('click', function () {
    const data = new FormData();
    data.append('p_creation_id', creation_id.innerText);
    const csrftoken = document.querySelector('[name=csrfmiddlewaretoken]').value;
    axios.defaults.headers.common['X-CSRFToken'] = csrftoken;
    axios.post('/INTERACT/publish_idea/', data, {
	    headers: {
            'Content-Type': 'multipart/form-data',
        },
    })
	.then(response => {
        console.log(response.data);
    })
    .catch(error => {
        console.error(error);
    });
});