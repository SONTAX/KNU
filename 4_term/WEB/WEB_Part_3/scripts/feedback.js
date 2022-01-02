function addEvent(elem, type, handler) {
    elem.addEventListener(type, handler, false);
    return false;
}

function check() {
    if (document.getElementById('feedback-name').checkValidity()
        && document.getElementById('feedback-email').checkValidity()
        && document.getElementById('feedback-tel').checkValidity()){
        alert("Спасибо за Ваш отзыв! В ближайшее время оператор свяжется с Вами!");
        document.getElementById('feedback-name').value = '';
        document.getElementById('feedback-email').value = '';
        document.getElementById('feedback-tel').value = '';
    } else {
        alert("Данные введены неверно!");
    }
}

addEvent(document.getElementById('feedback-button'), 'click', check);
