import java.time.LocalDate;
import java.util.*;

// "static void main" must be defined in a public class.
enum TaskStatus{
    TODO,
    IN_PROGRESS,
    DONE
}

enum TaskType{
    STORY, 
    FEATURE,
    BUG
}

class User{
    private final String id;
    private final String name;
    
    public User(String id, String name){
        this.id = id;
        this.name = name;
    }
    
    public String getId(){
        return id;
    }
    
    public String getName(){
        return name;
    }
}

class Task{
    private final String id;
    private final String title;
    private final TaskType type;
    private TaskStatus status;
    
    private final User assignee;    
    private final LocalDate dueDate;
    
    public Task(
        String id, String title, TaskType type, User assignee, LocalDate dueDate
    ){
        this.id = id;
        this.title = title;
        this.type = type;
        this.assignee = assignee;
        this.status = TaskStatus.TODO;
        this.dueDate = dueDate;
    }
    
    public String getId(){
        return id;
    }
    
    public User getAssignee(){
        return assignee;
    }
    
    public TaskStatus getStatus(){
        return status;
    }
    
    public void setStatus(TaskStatus status){
        this.status = status;
    }
    
    public LocalDate getDueDate(){
        return dueDate;
    }
    
    public String getTitle(){
        return title;
    }
    
    @Override
    public String toString(){
        return "Task{" +
            "id-'" + id + '\'' +
            ", title='" + title + '\'' + 
            ", type=" + type + 
            ", status=" + status + 
            ", assignee=" + assignee.getName() +
            '}';
    }
}

class Sprint{
    private final String id;
    private final String name;
    private final Map<String, Task> tasks;
    
    public Sprint(String id, String name){
        this.id = id;
        this.name = name;
        this.tasks = new HashMap<>();
    }
    
    public void addTask(Task task){
        tasks.put(task.getId(), task);
    }
    
    public void removeTask(String taskId){
        tasks.remove(taskId);
    }
    
    public Task getTask(String taskId){
        return tasks.get(taskId);
    }
    
    public Collection<Task> getAllTasks(){
        return tasks.values();
    }
    
    public String getId(){
        return id;
    }
}

class SprintService{
    public static final int MAX_IN_PROGRESS = 2;
    
    public void addTask(Sprint sprint, Task task){
        sprint.addTask(task);
    }
    
    public void removeTask(Sprint sprint, String taskId){
        sprint.removeTask(taskId);
    }
    
    public void changeTaskStatus(Sprint sprint, String taskId, TaskStatus newStatus){
        Task task = sprint.getTask(taskId);
        if(task==null){
            throw new IllegalArgumentException("Task not found");
        }
        
        if(newStatus == TaskStatus.IN_PROGRESS){
            long count = sprint.getAllTasks()
                .stream()
                .filter(t-> t.getAssignee().getId()
                        .equals(task.getAssignee().getId()))
                .filter(t->t.getStatus()==TaskStatus.IN_PROGRESS)
                .count();
            
            if(count>=MAX_IN_PROGRESS && task.getStatus()!=TaskStatus.IN_PROGRESS){
                throw new RuntimeException("User already has 2 tasks in progress");
            }
        }
        
        task.setStatus(newStatus);
    }
    
    public List<Task> getTaskAssignedToUser(Sprint sprint, String userId){
        return sprint.getAllTasks().stream()
            .filter(t->t.getAssignee().getId().equals(userId))
            .collect(Collectors.toList());
    }
    
    public List<Task> getDelayedTasks(Sprint sprint){
        LocalDate today = LocalDate.now();
        return sprint.getAllTasks().stream()
            .filter(task->task.getStatus() != TaskStatus.DONE)
            .filter(task->task.getDueDate().isBefore(today))
            .collect(Collectors.toList());
    }
}

public class Main {
    public static void main(String[] args) {
        User kirtee = new User("U1", "Kirtee");
        User rakesh = new User("U2", "Rakesh");
        
        Sprint sprint = new Sprint("S1", "Sprint-1");
        
        SprintService service = new SprintService();
        
        Task t1 = new Task("T1", 
                           "Login Page", 
                           TaskType.FEATURE, 
                           kirtee, 
                           LocalDate.now().plusDays(3));
        
        Task t2 = new Task("T2", 
                           "Payment Bug", 
                           TaskType.BUG, 
                           rakesh, 
                           LocalDate.now().plusDays(4));
        
        Task t3 = new Task("T3", 
                           "Profile Story", 
                           TaskType.STORY, 
                           rakesh, 
                           LocalDate.now().plusDays(1));
        
        Task t4 = new Task("T4", 
                           "Stats Graph", 
                           TaskType.FEATURE, 
                           rakesh, 
                           LocalDate.now().plusDays(2));
        
        service.addTask(sprint, t1);
        service.addTask(sprint, t2);
        service.addTask(sprint, t3);
        service.addTask(sprint, t4);
        
        service.changeTaskStatus(sprint, "T1", TaskStatus.IN_PROGRESS);
        
        service.changeTaskStatus(sprint, "T2", TaskStatus.IN_PROGRESS);
        
        service.changeTaskStatus(sprint, "T3", TaskStatus.IN_PROGRESS);
        
        try{
            service.changeTaskStatus(sprint, "T4", TaskStatus.IN_PROGRESS);
        } catch(Exception e){
            System.out.println(e.getMessage());
        }
        
        System.out.println(service.getTaskAssignedToUser(sprint, "U1"));
    }
}