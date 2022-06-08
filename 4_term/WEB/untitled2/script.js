function first(){
    let n1 = prompt("Input first array size: ","");
    let arr1 = [];
    for(let i = 0; i < n1; i++){
        arr1.push(prompt("Input number for first array: ", ""));
    }
    let n2 = prompt("Input second array size: ","");
    let arr2 = [];
    for(let i = 0; i < n2; i++){
        arr2.push(prompt("Input number for second array: ", ""));
    }
    let arr3 = [];
    for(let i = 0; i < n1; i++){
        if(arr3.indexOf(arr1[i]) < 0){
            arr3.push(arr1[i]);
        }
    }
    for(let i = 0; i < n2; i++){
        if(arr3.indexOf(arr2[i]) < 0){
            arr3.push(arr2[i]);
        }
    }
    arr3.forEach(element => alert(element));
}

function second(){
    let n = prompt("Input array size: ","");
    let arr = [];
    for(let i = 0; i < n; i++){
        arr.push(prompt("Input number: ", ""));
    }
    for(let i = 0; i < n; i++){
        if((arr[i]>0)&&((arr[i]%2)==0)){
            alert(arr[i]);
        }
    }
}

function third(){
    let n = prompt("Input array size: ","");
    let arr = [];
    for(let i = 0; i < n; i++){
        arr.push(prompt("Input number: ", ""));
    }
    for(let i = 0; i < n; i++){
        if(arr[i]==0){
            alert("message");
            return;
        }
    }
}

function fourth(){
    let n = prompt("Input array size: ","");
    let arr = [];
    for(let i = 0; i < n; i++){
        arr.push(prompt("Input number: ", ""));
    }
    alert(arr.indexOf('5'));
}

function fifth(){
    let n = prompt("Input array size: ","");
    let arr = [];
    let out = 1;
    for(let i = 0; i < n; i++){
        arr.push(prompt("Input number: ", ""));
    }
    for(let i = 0; i < n; i++){
        out *= arr[i];
    }
    alert(out);
}

function sixth_a(){
    let n = prompt("Input array size: ","");
    let arr = [];
    for(let i = 0; i < n; i++){
        arr.push(prompt("Input string: ", ""));
    }
    arr.sort(compare_a);
    let s = "Sorted array: ";
    arr.forEach(element => s+=element+" ");
    alert(s);
}

function compare_a(value1, value2){
    if (value1 < value2) {
        return -1;
    } else if (value1 > value2) {
        return 1;
    } else {
        return 0;
    }
}

function sixth_b(){
    let n = prompt("Input array size: ","");
    let arr = [];
    for(let i = 0; i < n; i++){
        arr.push(prompt("Input number: ", ""));
    }
    arr.sort(compare_b);
    let s = "Sorted array: ";
    arr.forEach(element => s+=element+" ");
    alert(s);
}

function compare_b(value1, value2){
    if (Math.abs(value1) < Math.abs(value2)) {
        return -1;
    } else if (Math.abs(value1) > Math.abs(value2)) {
        return 1;
    } else {
        return 0;
    }
}