document.addEventListener("DOMContentLoaded", () => {
    const tabs = document.querySelectorAll(".tab");
    const conteudos = document.querySelectorAll(".tab-conteudo");

    tabs.forEach(tab => {
        tab.addEventListener("click", () => {
            // remove classe 'ativo' de todas as abas e conteúdos
            tabs.forEach(t => t.classList.remove("ativo"));
            conteudos.forEach(c => c.classList.remove("ativo"));
            tab.classList.add("ativo");
            const target = tab.getAttribute("data-tab");
            document.querySelector(`.tab-conteudo[data-tab="${target}"]`).classList.add("ativo");
        });
    });
});