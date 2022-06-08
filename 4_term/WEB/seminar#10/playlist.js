window.onload = init;

function init() {
    let buttonAdd = document.getElementById("addButton");
    buttonAdd.onclick = handleButtonClick;
    let buttonDelete = document.getElementById("deleteButton");
    buttonDelete.onclick = handleButtonDeleteClick;
    loadPlaylist();
}

function handleButtonClick() {
    let textInput = document.getElementById("songTextInput");
    let songName = textInput.value;
    let playlistArray = getStoreArray("playlist");
    if (playlistArray.indexOf(songName) === -1) {
        let li = document.createElement("li");
        li.innerHTML = songName;
        let ul = document.getElementById("playlist");
        ul.appendChild(li);
        save(songName);
    }
    document.getElementById("songTextInput").value = "";
}

function handleButtonDeleteClick() {
    let textDelete = document.getElementById("songTextDelete");
    let songNameDelete = textDelete.value;
    let playlistArray = getStoreArray("playlist");
    if (playlistArray.indexOf(songNameDelete) !== -1) {
        let element = document.getElementById("playlist");
        while (element.firstChild) {
            element.removeChild(element.firstChild);
        }
        delete_(songNameDelete);
        loadPlaylist();
    }
    document.getElementById("songTextDelete").value = "";
}