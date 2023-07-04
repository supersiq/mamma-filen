//alert - upon opening site
//alert('hell');
//console - in the console
console.log('hell2')
console.error('hell_error')
console.warn('hell_warn')

//let - to be reassigned
//let age = 1;
//const - static
const real_age = 10;
//console.log(age)
console.log(real_age)

const name = 'jonathan';
const age = 100;
const rating = 2.5;
const isSwag = true;
const x = null;
const y = undefined;
let z;
//concatenation
console.log('my name is : ' + name + ' and i am :' + age);
//template strings
const hello = `my nama ${name} and i be ${age}`;
console.log(hello);
const s = 'apple, banana, pear';
console.log(s.length);
//output: 5
console.log(s.toUpperCase());
//output HELL0
console.log(s);

console.log(s.substring(0, 3).toUpperCase());
//output HEL
console.log(s.split(', '));

const numbers = new Array(1, 2, 3, 4, 5);
const animals = ['dog', 'cat', 'egg'];
//arrays are 0-based
console.log(animals[2]);

