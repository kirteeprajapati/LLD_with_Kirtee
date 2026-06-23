// Doctor, Patient, Appointment, TimeSlot, Waitlist
import java.time.LocalDateTime;

enum SlotStatus{
    AVAILABLE,
    BOOKED, 
}

enum Specialization {
    CARDIOLOGIST,
    ORTHOPEDIC,
    DERMATOLOGIST
}

class Patient{
    private final String id;
    private final String name;
    
    public Patient(String id, String name){
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

class Slot{
    private final LocalDateTime startTime;
    private Patient bookedPatient;
    private Queue<Patient> waitList;
    
    public Slot(LocalDateTime startTime){
        this.startTime = startTime;
        this.waitList = new LinkedList<>();
    }
    
    public boolean isAvailable(){
        return bookedPatient == null;
    }
    
    public Patient getBookedPatient(){
        return bookedPatient;
    }
    
    public void setBookedPatient(Patient patient){
        this.bookedPatient = patient;
    }
    
    public Queue<Patient> getWaitList(){
        return waitList;
    }
    
    public LocalDateTime getStartTime(){
        return startTime; 
    }
}

class Doctor{
    private final String id;
    private final String name;
    private final Specialization specialization;
    private final Map<String, Slot> slots;
    
    public Doctor(String id, String name, Specialization specialization){
        this.id = id;
        this.name = name;
        this.specialization = specialization;
        this.slots = new HashMap<>();
    }
    
    public void addSlot(Slot slot){
        slots.put(slot.getStartTime().toString(), slot);
    }
    
    public Slot getSlots(String slotKey){
        return slots.get(slotKey);
    }
    
    public Map<String, Slot> getSlots(){
        return slots;
    }
    
    public String getName(){
        return name;
    }
    
    public Specialization getSpecialization(){
        return specialization;
    }
}

class Appointment{
    private final Doctor doctor;
    private final Patient patient;
    private final Slot slot;
    public Appointment(Doctor doctor, Patient patient, Slot slot){
        this.doctor = doctor;
        this.patient = patient;
        this.slot = slot;
    }
    
    @Override
    public String toString(){
        return patient.getName() 
            + " -> " 
            + doctor.getName() 
            + " @ " 
            + slot.getStartTime();
    }
}

class BookingService{
    private final Map<String, Doctor> doctors = new HashMap<>();
    private final Map<String, Patient> patients = new HashMap<>();
    private final List<Appointment> appointments = new ArrayList<>();
    
    public void registerDoctor(Doctor doctor){
        doctors.put(doctor.getName(), doctor);
    }
    
    public void registerPatient(Patient patient){
        patients.put(patient.getId().toString(), patient);
    }
    
    public void bookAppointment(Doctor doctor, 
                                Patient patient, 
                                String slotKey){
        Slot slot = doctor.getSlots(slotKey);
        if(slot==null){
            throw new RuntimeException("Slot not found");
        }
        
        if(slot.isAvailable()){
            slot.setBookedPatient(patient);
            
            appointments.add(new Appointment(
            doctor, patient, slot));
            
            System.out.println(doctor.getName() + " Booked successfully for patient " + patient.getName() + " At the slot: " + slot.getStartTime());
        } else if ( slot.getBookedPatient().getId().equals(patient.getId())){
            System.out.println("Patient already has this slot booked");
        }
        else{
            slot.getWaitList().offer(patient);
            System.out.println("Added to waitlist");
        }
    }
    
    public void cancelAppointment(Doctor doctor, String slotKey){
        Slot slot = doctor.getSlots(slotKey);
        
        if(slot==null || slot.isAvailable()){
            return;
        }
        
        if(!slot.getWaitList().isEmpty()){
            Patient next = slot.getWaitList().poll();
            slot.setBookedPatient(next);
            System.out.println("Slot transferred to " + next.getName());
        } else{
            slot.setBookedPatient(null);
        }
    }
    
    public void showDoctorAppointments(Doctor doctor){
        for(Appointment appointment : appointments){
            if(appointment.toString().contains(doctor.getName())){
                System.out.println(appointment);
            }
        }
    }
}
 
public class Main{
    public static void main(String[] args){
        BookingService service = new BookingService();
        
        Doctor doctor = new Doctor("D1", "Dr Meena", Specialization.CARDIOLOGIST);
        
        Slot slot1 = new Slot(LocalDateTime.of(2026, 6, 25, 10, 0));
        
        doctor.addSlot(slot1);
        
        Patient p1 = new Patient("P1", "Kirtee");
        Patient p2 = new Patient("P2", "Rakesh");
        
        service.registerDoctor(doctor);
        service.registerPatient(p1);
        service.registerPatient(p2);
        
        String slotKey = slot1.getStartTime().toString();
        
        service.bookAppointment(doctor, p1, slotKey);
        service.bookAppointment(doctor, p2, slotKey);
        service.cancelAppointment(doctor, slotKey);
        service.bookAppointment(doctor, p2, slotKey);
        
    }
}