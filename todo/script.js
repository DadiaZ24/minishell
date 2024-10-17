document.addEventListener('DOMContentLoaded', function() {
    // Load the saved status of tasks from the API
    loadStatus();

    // Add event listeners to checkboxes
    const checkboxes = document.querySelectorAll('input[type="checkbox"]');
    checkboxes.forEach(checkbox => {
        checkbox.addEventListener('change', function() {
            updateTaskStatus(this);
        });
    });
});

function updateTaskStatus(checkbox) {
    const taskText = checkbox.nextElementSibling;
    if (checkbox.checked) {
        taskText.classList.add('done');
    } else {
        taskText.classList.remove('done');
    }
}

async function saveStatus() {
    const tasks = {};
    const taskElements = document.querySelectorAll('input[type="checkbox"]');
    
    taskElements.forEach(task => {
        tasks[task.id] = task.checked;
    });

    const json = JSON.stringify({ tasks: tasks });

    // Make a POST request to save tasks to the API
    try {
        const response = await fetch('http://localhost:3000/api/tasks', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: json
        });

        if (response.ok) {
            alert('Progress saved successfully!');
        } else {
            alert('Error saving progress');
        }
    } catch (error) {
        console.error('Error saving tasks:', error);
        alert('Error saving progress');
    }
}

async function loadStatus() {
    // Make a GET request to load tasks from the API
    try {
        const response = await fetch('http://localhost:3000/api/tasks');
        const data = await response.json();
        const tasks = data.tasks;

        const taskElements = document.querySelectorAll('input[type="checkbox"]');
        taskElements.forEach(task => {
            if (tasks[task.id] !== undefined) {
                task.checked = tasks[task.id];
                task.nextElementSibling.classList.toggle('done', tasks[task.id]);
            }
        });
    } catch (error) {
        console.error('Error loading tasks:', error);
    }
}
