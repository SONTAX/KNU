let itemBox = document.querySelectorAll('.product');
let cartCont = document.getElementById('cart-wrapper');
let full_price = 0;

function addEvent(elem, type, handler) {
    elem.addEventListener(type, handler, false);
    return false;
}

function getCartData() {
    return JSON.parse(localStorage.getItem('cart_content'));
}

function setCartData(o) {
    localStorage.setItem('cart_content', JSON.stringify(o));
    return false;
}

function clearCart() {
    localStorage.removeItem('cart_content');
    full_price = 0;
    openCart();
}

function buyConfirm() {
    alert("Спасибо за покупку! В течении дня ожидайте звонка от менеджера.");
    clearCart();
}

function addToCart(e) {
    this.disabled = true
    let cartData = getCartData() || {};
    let parentBox = this.parentNode.parentNode;
    let itemId = this.getAttribute('data-id').toString();
    let itemTitle = parentBox.querySelector('.item-name').innerHTML;
    let itemPrice = parentBox.querySelector('.item-price').innerHTML;
    if (cartData.hasOwnProperty(itemId)) {
        cartData[itemId][2]++;
    } else {
        cartData[itemId] = [itemTitle, itemPrice, 1, itemId];
    }
    if (!setCartData(cartData)) {
        this.disabled = false;
    }
    return false;
}

for (let i = 0; i < itemBox.length; i++) {
    addEvent(itemBox[i].querySelector('.add_item'), 'click', addToCart);
}

function openCart(e){
    let cartData = getCartData();
    let totalItems = '<table class="shopping_list"><tr><th>Наименование</th><th>Цена</th><th>Кол-во</th><th>Стоимость</th></tr>';
    if (cartData !== null) {
        for (let items in cartData) {
            totalItems += '<tr>';
            for (let i = 0; i < cartData[items].length - 1; i++) {
                if (i === 1) {
                    totalItems += '<td>' + cartData[items][i] + '₴' + '</td>';
                } else {
                    totalItems += '<td>' + cartData[items][i] + '</td>';
                }
            }
            full_price += Number(cartData[items][1] * cartData[items][2]);
            totalItems += '<td>' + (cartData[items][1] * cartData[items][2]) + '₴' + '</td>';
            totalItems += '</tr>';
        }
        totalItems += '</table>' + '<p><h4>' + 'Полная стоимость: ' + full_price + '₴' + '</h4></p>'
            + '<button class="btn btn-success btn-sm" id="confirm_buy" onclick="buyConfirm()">Оформить заказ</button><br>' +
            '<button class="btn btn-warning btn-sm" id="clear_cart" onclick="clearCart()">Очистить корзину</button>';
        cartCont.innerHTML = totalItems;
    } else {
        cartCont.innerHTML = '<p>Корзина пустая!</p>';
    }
    return false;
}

addEvent(document.getElementById('cart-text'), 'click', openCart);